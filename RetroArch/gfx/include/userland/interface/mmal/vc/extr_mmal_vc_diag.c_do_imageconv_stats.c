#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stats ;
typedef  int VC_MEM_ADDR_T ;
typedef  int /*<<< orphan*/  VC_MEM_ACCESS_HANDLE_T ;
struct TYPE_5__ {int magic; int conversions; long time_spent; double last_image_ts; double first_image_ts; double size_requests; double max_vrf_delay; double vrf_wait_time; double duplicate_conversions; double failures; double max_delay; } ;
typedef  TYPE_1__ IMAGECONV_STATS_T ;

/* Variables and functions */
 int /*<<< orphan*/  CloseVideoCoreMemory (int /*<<< orphan*/ ) ; 
 int IMAGECONV_STATS_MAGIC ; 
 int /*<<< orphan*/  LookupVideoCoreSymbol (int /*<<< orphan*/ ,char*,int*,size_t*) ; 
 int OpenVideoCoreMemory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadVideoCoreMemory (int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ReadVideoCoreUInt32 (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  WriteVideoCoreMemory (int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,double) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static int do_imageconv_stats(int argc, const char **argv)
{
   VC_MEM_ACCESS_HANDLE_T vc;
   VC_MEM_ADDR_T addr, statsaddr;
   size_t size;
   IMAGECONV_STATS_T stats;
   long convert_time;
   double frame_rate;
   int rc;
   int reset_stats = 0;

   if (argc > 2)
      reset_stats = strcasecmp(argv[2], "reset") == 0;

   if ((rc = OpenVideoCoreMemory(&vc)) < 0)
   {
      fprintf(stderr,"Unable to open videocore memory: %d\n", rc);
      return -1;
   }
   if (!LookupVideoCoreSymbol(vc, "imageconv_stats", &addr, &size))
   {
      fprintf(stderr,"Could not get imageconv stats address\n");
      goto fail;
   }
   if (!ReadVideoCoreUInt32(vc, &statsaddr, addr))
   {
      fprintf(stderr, "Could not read imageconv stats address\n");
      goto fail;
   }

   if (reset_stats)
   {
      memset(&stats, 0, sizeof(stats));
      stats.magic = IMAGECONV_STATS_MAGIC;
      if (!WriteVideoCoreMemory(vc, &stats, statsaddr, sizeof(stats)))
      {
         fprintf(stderr, "Could not write stats at 0x%x\n", statsaddr);
         goto fail;
      }
   }

   if (!ReadVideoCoreMemory(vc, &stats, statsaddr, sizeof(stats)))
   {
      fprintf(stderr, "Could not read stats at 0x%x\n", statsaddr);
      goto fail;
   }

   if (stats.magic != IMAGECONV_STATS_MAGIC)
   {
      fprintf(stderr, "Bad magic 0x%x\n", stats.magic);
      goto fail;
   }

   if (stats.conversions)
      convert_time = stats.time_spent / stats.conversions;
   else
      convert_time = 0;

   if (stats.conversions)
      frame_rate = 1000000.0 * stats.conversions /
         (stats.last_image_ts - stats.first_image_ts);
   else
      frame_rate = 0;

   printf("%-25s:\t%d\n", "conversions", stats.conversions);
   printf("%-25s:\t%d\n", "size requests", stats.size_requests);
   printf("%-25s:\t%d\n", "max vrf delay", stats.max_vrf_delay);
   printf("%-25s:\t%d\n", "vrf wait time", stats.vrf_wait_time);
   printf("%-25s:\t%d\n", "duplicate conversions", stats.duplicate_conversions);
   printf("%-25s:\t%d\n", "failures", stats.failures);
   printf("%-25s:\t%ld\n", "convert time / image (us)", convert_time);
   printf("%-25s:\t%.1f\n", "client frame_rate", frame_rate);
   printf("%-25s:\t%d us\n", "max delay to consume", stats.max_delay);

   CloseVideoCoreMemory(vc);
   return 0;
fail:
   CloseVideoCoreMemory(vc);
   return -1;

}
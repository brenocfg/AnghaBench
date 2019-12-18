#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;
struct TYPE_2__ {int /*<<< orphan*/  fourcc; int /*<<< orphan*/  variant; scalar_t__ codecid; } ;

/* Variables and functions */
 TYPE_1__* codecid_to_fourcc_table ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static VC_CONTAINER_FOURCC_T mkv_codecid_to_fourcc(const char *codecid,
   VC_CONTAINER_FOURCC_T *variant)
{
   unsigned int i;
   for(i = 0; codecid_to_fourcc_table[i].codecid; i++)
      if(!strcmp(codecid_to_fourcc_table[i].codecid, codecid)) break;
   if (variant) *variant = codecid_to_fourcc_table[i].variant;
   return codecid_to_fourcc_table[i].fourcc;
}
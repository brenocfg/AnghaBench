#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct coff_sfile {struct coff_sfile* next; } ;
struct coff_ofile {struct coff_sfile* source_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  file ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_ed (struct coff_ofile*,struct coff_sfile*,int) ; 
 int /*<<< orphan*/  wr_er (struct coff_ofile*,struct coff_sfile*,int) ; 
 int wr_sc (struct coff_ofile*,struct coff_sfile*) ; 
 int /*<<< orphan*/  wr_un (struct coff_ofile*,struct coff_sfile*,int,int) ; 

__attribute__((used)) static void
wr_unit_info (struct coff_ofile *ptr)
{
  struct coff_sfile *sfile;
  int first = 1;

  for (sfile = ptr->source_head;
       sfile;
       sfile = sfile->next)
    {
      long p1;
      long p2;
      int nsecs;

      p1 = ftell (file);
      wr_un (ptr, sfile, first, 0);
      nsecs = wr_sc (ptr, sfile);
      p2 = ftell (file);
      fseek (file, p1, SEEK_SET);
      wr_un (ptr, sfile, first, nsecs);
      fseek (file, p2, SEEK_SET);
      wr_er (ptr, sfile, first);
      wr_ed (ptr, sfile, first);
      first = 0;
    }
}
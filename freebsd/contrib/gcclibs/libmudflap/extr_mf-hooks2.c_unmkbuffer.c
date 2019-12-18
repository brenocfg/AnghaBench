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
struct mf_filebuffer {struct mf_filebuffer* next; struct mf_filebuffer* buffer; int /*<<< orphan*/ * file; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mf_filebuffer*) ; 
 struct mf_filebuffer* mf_filebuffers ; 

__attribute__((used)) static void
unmkbuffer (FILE *f)
{
  struct mf_filebuffer *b = mf_filebuffers;
  struct mf_filebuffer **pb = & mf_filebuffers;
  while (b != NULL)
    {
      if (b->file == f)
        {
          *pb = b->next;
          free (b->buffer);
          free (b);
          return;
        }
      pb = & b->next;
      b = b->next;
    }
}
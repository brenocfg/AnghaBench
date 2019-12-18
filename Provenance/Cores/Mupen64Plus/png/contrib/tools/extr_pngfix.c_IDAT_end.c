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
struct file {int /*<<< orphan*/  state; int /*<<< orphan*/ * chunk; } ;
struct IDAT {struct file* file; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct IDAT) ; 
 int /*<<< orphan*/  STATE_CHUNKS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_end (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
IDAT_end(struct IDAT **idat_var)
{
   struct IDAT *idat = *idat_var;
   struct file *file = idat->file;

   *idat_var = NULL;

   CLEAR(*idat);

   assert(file->chunk != NULL);
   chunk_end(&file->chunk);

   /* Regardless of why the IDAT was killed set the state back to CHUNKS (it may
    * already be CHUNKS because the state isn't changed until process_IDAT
    * returns; a stop will cause IDAT_end to be entered in state CHUNKS!)
    */
   file->state = STATE_CHUNKS;
}
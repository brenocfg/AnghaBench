#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ curl_off_t ;
struct TYPE_3__ {int /*<<< orphan*/  kind; int /*<<< orphan*/  encstate; scalar_t__ datasize; int /*<<< orphan*/ * fp; int /*<<< orphan*/ * data; void* arg; int /*<<< orphan*/  (* freefunc ) (void*) ;int /*<<< orphan*/ * seekfunc; int /*<<< orphan*/ * readfunc; } ;
typedef  TYPE_1__ curl_mimepart ;

/* Variables and functions */
 int /*<<< orphan*/  MIMEKIND_NONE ; 
 int /*<<< orphan*/  cleanup_encoder_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void cleanup_part_content(curl_mimepart *part)
{
  if(part->freefunc)
    part->freefunc(part->arg);

  part->readfunc = NULL;
  part->seekfunc = NULL;
  part->freefunc = NULL;
  part->arg = (void *) part;          /* Defaults to part itself. */
  part->data = NULL;
  part->fp = NULL;
  part->datasize = (curl_off_t) 0;    /* No size yet. */
  cleanup_encoder_state(&part->encstate);
  part->kind = MIMEKIND_NONE;
}
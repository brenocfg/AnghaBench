#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* gz_statep ;
typedef  int /*<<< orphan*/ * gzFile ;
struct TYPE_4__ {scalar_t__ have; } ;
struct TYPE_5__ {scalar_t__ mode; scalar_t__ how; int direct; TYPE_1__ x; } ;

/* Variables and functions */
 scalar_t__ GZ_READ ; 
 scalar_t__ LOOK ; 
 int /*<<< orphan*/  gz_look (TYPE_2__*) ; 

int gzdirect(gzFile file)
{
   gz_statep state;

   /* get internal structure */
   if (file == NULL)
      return 0;
   state = (gz_statep)file;

   /* if the state is not known, but we can find out, then do so (this is
      mainly for right after a gzopen() or gzdopen()) */
   if (state->mode == GZ_READ && state->how == LOOK && state->x.have == 0)
      (void)gz_look(state);

   /* return 1 if transparent, 0 if processing a gzip stream */
   return state->direct;
}
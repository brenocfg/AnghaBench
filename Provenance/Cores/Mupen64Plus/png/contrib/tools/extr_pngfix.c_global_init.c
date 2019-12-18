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
struct global {int /*<<< orphan*/  idat_cache; scalar_t__ status_code; int /*<<< orphan*/  skip; scalar_t__ optimize_zlib; scalar_t__ idat_max; scalar_t__ verbose; scalar_t__ quiet; scalar_t__ warnings; scalar_t__ errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct global) ; 
 int /*<<< orphan*/  IDAT_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SKIP_NONE ; 

__attribute__((used)) static void
global_init(struct global *global)
   /* Call this once (and only once) to initialize the control */
{
   CLEAR(*global);

   /* Globals */
   global->errors        = 0;
   global->warnings      = 0;
   global->quiet         = 0;
   global->verbose       = 0;
   global->idat_max      = 0;         /* no re-chunking of IDAT */
   global->optimize_zlib = 0;
   global->skip          = SKIP_NONE;
   global->status_code   = 0;

   IDAT_list_init(&global->idat_cache);
}
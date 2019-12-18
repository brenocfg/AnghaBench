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
struct global {int status_code; int /*<<< orphan*/  idat_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct global) ; 
 int /*<<< orphan*/  IDAT_list_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
global_end(struct global *global)
{

   int rc;

   IDAT_list_end(&global->idat_cache);
   rc = global->status_code;
   CLEAR(*global);
   return rc;
}
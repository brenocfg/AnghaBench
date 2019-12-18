#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  saved; } ;
typedef  TYPE_1__ png_store ;

/* Variables and functions */
 int /*<<< orphan*/  store_freefile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_image_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_read_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  store_write_reset (TYPE_1__*) ; 

__attribute__((used)) static void
store_delete(png_store *ps)
{
   store_write_reset(ps);
   store_read_reset(ps);
   store_freefile(&ps->saved);
   store_image_free(ps, NULL);
}
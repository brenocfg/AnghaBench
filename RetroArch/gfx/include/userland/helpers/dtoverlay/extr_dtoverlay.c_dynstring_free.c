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
struct dynstring {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dynstring_init (struct dynstring*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dynstring_free(struct dynstring *ds)
{
   free(ds->buf);
   dynstring_init(ds);
}
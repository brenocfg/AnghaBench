#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ctb_strtab; } ;
typedef  TYPE_1__ ctf_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ctf_buf_grow (TYPE_1__*) ; 
 int /*<<< orphan*/  strtab_create (int /*<<< orphan*/ *) ; 
 TYPE_1__* xcalloc (int) ; 

__attribute__((used)) static ctf_buf_t *
ctf_buf_new(void)
{
	ctf_buf_t *b = xcalloc(sizeof (ctf_buf_t));

	strtab_create(&b->ctb_strtab);
	ctf_buf_grow(b);

	return (b);
}
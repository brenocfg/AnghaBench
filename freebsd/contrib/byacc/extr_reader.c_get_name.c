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
typedef  int /*<<< orphan*/  bucket ;

/* Variables and functions */
 scalar_t__ IS_IDENT (int) ; 
 int NUL ; 
 int /*<<< orphan*/  cache ; 
 int /*<<< orphan*/  cachec (int) ; 
 scalar_t__ cinc ; 
 int* cptr ; 
 scalar_t__ is_reserved (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  used_reserved (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bucket *
get_name(void)
{
    int c;

    cinc = 0;
    for (c = *cptr; IS_IDENT(c); c = *++cptr)
	cachec(c);
    cachec(NUL);

    if (is_reserved(cache))
	used_reserved(cache);

    return (lookup(cache));
}
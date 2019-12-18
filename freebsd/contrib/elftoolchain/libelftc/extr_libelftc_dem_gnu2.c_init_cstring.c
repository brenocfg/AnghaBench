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
struct cstring {size_t size; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/ * malloc (int) ; 

__attribute__((used)) static bool
init_cstring(struct cstring *s, size_t len)
{

	if (s == NULL || len <= 1)
		return (false);

	if ((s->buf = malloc(sizeof(char) * len)) == NULL)
		return (false);

	s->size = len - 1;

	return (true);
}
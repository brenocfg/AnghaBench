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
struct conf {int /*<<< orphan*/  c_rmask; int /*<<< orphan*/  c_family; int /*<<< orphan*/  c_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  fmtmask (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmtname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static const char *
conf_namemask(char *b, size_t l, const struct conf *c)
{
	strlcpy(b, fmtname(c->c_name), l);
	fmtmask(b, l, c->c_family, c->c_rmask);
	return b;
}
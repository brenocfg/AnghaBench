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
struct pf_rule {int match_tag; scalar_t__ match_tag_not; } ;
struct pf_mtag {int pftag_tag; } ;

/* Variables and functions */

__attribute__((used)) static int
pf_match_tag(struct pf_rule *r, struct pf_mtag *pf_mtag,
    int *tag)
{
	if (*tag == -1)
		*tag = pf_mtag->pftag_tag;

	return ((!r->match_tag_not && r->match_tag == *tag) ||
	    (r->match_tag_not && r->match_tag != *tag));
}
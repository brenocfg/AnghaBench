#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fts_info; scalar_t__ fts_level; } ;
typedef  TYPE_1__ FTSENT ;

/* Variables and functions */
 int FTS_D ; 
 int FTS_ERR ; 
 int FTS_NS ; 
 scalar_t__ FTS_ROOTLEVEL ; 
 int /*<<< orphan*/  f_listdir ; 
 int namecmp (TYPE_1__ const* const,TYPE_1__ const* const) ; 
 int sortfcn (TYPE_1__ const* const,TYPE_1__ const* const) ; 

__attribute__((used)) static int
mastercmp(const FTSENT * const *a, const FTSENT * const *b)
{
	int a_info, b_info;

	a_info = (*a)->fts_info;
	if (a_info == FTS_ERR)
		return (0);
	b_info = (*b)->fts_info;
	if (b_info == FTS_ERR)
		return (0);

	if (a_info == FTS_NS || b_info == FTS_NS)
		return (namecmp(*a, *b));

	if (a_info != b_info &&
	    (*a)->fts_level == FTS_ROOTLEVEL && !f_listdir) {
		if (a_info == FTS_D)
			return (1);
		if (b_info == FTS_D)
			return (-1);
	}
	return (sortfcn(*a, *b));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct ldtentry {int next; int namlen; int /*<<< orphan*/ * name; } ;
struct idtentry {int next; int namlen; int /*<<< orphan*/ * name; } ;
struct dtslot {int next; int /*<<< orphan*/ * name; } ;
struct component_name {int namlen; int /*<<< orphan*/ * name; } ;
typedef  int s8 ;
struct TYPE_5__ {int flag; } ;
struct TYPE_6__ {struct dtslot* slot; TYPE_1__ header; } ;
typedef  TYPE_2__ dtpage_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int BT_LEAF ; 
 int /*<<< orphan*/  DTIHDRDATALEN ; 
 int /*<<< orphan*/  DTLHDRDATALEN ; 
 int /*<<< orphan*/  DTLHDRDATALEN_LEGACY ; 
 int /*<<< orphan*/  DTSLOTDATALEN ; 
 int* DT_GETSTBL (TYPE_2__*) ; 
 int JFS_DIR_INDEX ; 
 int /*<<< orphan*/  UniStrncpy_from_le (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dtGetKey(dtpage_t * p, int i,	/* entry index */
		     struct component_name * key, int flag)
{
	int si;
	s8 *stbl;
	struct ldtentry *lh;
	struct idtentry *ih;
	struct dtslot *t;
	int namlen, len;
	wchar_t *kname;
	__le16 *name;

	/* get entry */
	stbl = DT_GETSTBL(p);
	si = stbl[i];
	if (p->header.flag & BT_LEAF) {
		lh = (struct ldtentry *) & p->slot[si];
		si = lh->next;
		namlen = lh->namlen;
		name = lh->name;
		if (flag & JFS_DIR_INDEX)
			len = min(namlen, DTLHDRDATALEN);
		else
			len = min(namlen, DTLHDRDATALEN_LEGACY);
	} else {
		ih = (struct idtentry *) & p->slot[si];
		si = ih->next;
		namlen = ih->namlen;
		name = ih->name;
		len = min(namlen, DTIHDRDATALEN);
	}

	key->namlen = namlen;
	kname = key->name;

	/*
	 * move head/only segment
	 */
	UniStrncpy_from_le(kname, name, len);

	/*
	 * move additional segment(s)
	 */
	while (si >= 0) {
		/* get next segment */
		t = &p->slot[si];
		kname += len;
		namlen -= len;
		len = min(namlen, DTSLOTDATALEN);
		UniStrncpy_from_le(kname, t->name, len);

		si = t->next;
	}
}
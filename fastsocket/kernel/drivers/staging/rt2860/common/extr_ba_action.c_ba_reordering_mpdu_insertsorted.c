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
struct reordering_mpdu {struct reordering_mpdu* next; int /*<<< orphan*/  Sequence; } ;
struct reordering_list {int /*<<< orphan*/  qlen; struct reordering_mpdu* next; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAXSEQ ; 
 scalar_t__ SEQ_SMALLER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN ba_reordering_mpdu_insertsorted(struct reordering_list *list, struct reordering_mpdu *mpdu)
{

	struct reordering_mpdu **ppScan = &list->next;

	while (*ppScan != NULL)
	{
		if (SEQ_SMALLER((*ppScan)->Sequence, mpdu->Sequence, MAXSEQ))
		{
			ppScan = &(*ppScan)->next;
		}
		else if ((*ppScan)->Sequence == mpdu->Sequence)
		{
			/* give up this duplicated frame */
			return(FALSE);
		}
		else
		{
			/* find position */
			break;
		}
	}

	mpdu->next = *ppScan;
	*ppScan = mpdu;
	list->qlen++;
	return TRUE;
}
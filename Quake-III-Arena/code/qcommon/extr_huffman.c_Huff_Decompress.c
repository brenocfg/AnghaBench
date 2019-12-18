#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int cursize; int* data; int maxsize; } ;
typedef  TYPE_1__ msg_t ;
struct TYPE_8__ {TYPE_4__* tree; TYPE_4__* lhead; int /*<<< orphan*/  blocNode; TYPE_4__* nodeList; TYPE_4__** loc; TYPE_4__* ltail; } ;
typedef  TYPE_2__ huff_t ;
typedef  int byte ;
struct TYPE_9__ {size_t symbol; int /*<<< orphan*/ * right; int /*<<< orphan*/  left; int /*<<< orphan*/  parent; int /*<<< orphan*/ * prev; int /*<<< orphan*/  next; scalar_t__ weight; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Huff_Receive (TYPE_4__*,int*,int*) ; 
 int /*<<< orphan*/  Huff_addRef (TYPE_2__*,int) ; 
 size_t NYT ; 
 int bloc ; 
 int get_bit (int*) ; 

void Huff_Decompress(msg_t *mbuf, int offset) {
	int			ch, cch, i, j, size;
	byte		seq[65536];
	byte*		buffer;
	huff_t		huff;

	size = mbuf->cursize - offset;
	buffer = mbuf->data + offset;

	if ( size <= 0 ) {
		return;
	}

	Com_Memset(&huff, 0, sizeof(huff_t));
	// Initialize the tree & list with the NYT node 
	huff.tree = huff.lhead = huff.ltail = huff.loc[NYT] = &(huff.nodeList[huff.blocNode++]);
	huff.tree->symbol = NYT;
	huff.tree->weight = 0;
	huff.lhead->next = huff.lhead->prev = NULL;
	huff.tree->parent = huff.tree->left = huff.tree->right = NULL;

	cch = buffer[0]*256 + buffer[1];
	// don't overflow with bad messages
	if ( cch > mbuf->maxsize - offset ) {
		cch = mbuf->maxsize - offset;
	}
	bloc = 16;

	for ( j = 0; j < cch; j++ ) {
		ch = 0;
		// don't overflow reading from the messages
		// FIXME: would it be better to have a overflow check in get_bit ?
		if ( (bloc >> 3) > size ) {
			seq[j] = 0;
			break;
		}
		Huff_Receive(huff.tree, &ch, buffer);				/* Get a character */
		if ( ch == NYT ) {								/* We got a NYT, get the symbol associated with it */
			ch = 0;
			for ( i = 0; i < 8; i++ ) {
				ch = (ch<<1) + get_bit(buffer);
			}
		}
    
		seq[j] = ch;									/* Write symbol */

		Huff_addRef(&huff, (byte)ch);								/* Increment node */
	}
	mbuf->cursize = cch + offset;
	Com_Memcpy(mbuf->data + offset, seq, cch);
}
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
struct TYPE_5__ {unsigned char key; int nbits; int nbytes; int framelen; int SyncInit; int dbit; int skbres; int maxsize; int /*<<< orphan*/ * encodebuf; scalar_t__ b; scalar_t__ introducer; int /*<<< orphan*/  OfflineFrame; int /*<<< orphan*/  OnlineFrame; scalar_t__ decodelen; } ;
typedef  TYPE_1__ isdn_v110_stream ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  V110_19200 129 
#define  V110_38400 128 
 int /*<<< orphan*/  V110_OffMatrix_19200 ; 
 int /*<<< orphan*/  V110_OffMatrix_38400 ; 
 int /*<<< orphan*/  V110_OffMatrix_9600 ; 
 int /*<<< orphan*/  V110_OnMatrix_19200 ; 
 int /*<<< orphan*/  V110_OnMatrix_38400 ; 
 int /*<<< orphan*/  V110_OnMatrix_9600 ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static isdn_v110_stream *
isdn_v110_open(unsigned char key, int hdrlen, int maxsize)
{
	int i;
	isdn_v110_stream *v;

	if ((v = kzalloc(sizeof(isdn_v110_stream), GFP_ATOMIC)) == NULL)
		return NULL;
	v->key = key;
	v->nbits = 0;
	for (i = 0; key & (1 << i); i++)
		v->nbits++;

	v->nbytes = 8 / v->nbits;
	v->decodelen = 0;

	switch (key) {
		case V110_38400:
			v->OnlineFrame = V110_OnMatrix_38400;
			v->OfflineFrame = V110_OffMatrix_38400;
			break;
		case V110_19200:
			v->OnlineFrame = V110_OnMatrix_19200;
			v->OfflineFrame = V110_OffMatrix_19200;
			break;
		default:
			v->OnlineFrame = V110_OnMatrix_9600;
			v->OfflineFrame = V110_OffMatrix_9600;
			break;
	}
	v->framelen = v->nbytes * 10;
	v->SyncInit = 5;
	v->introducer = 0;
	v->dbit = 1;
	v->b = 0;
	v->skbres = hdrlen;
	v->maxsize = maxsize - hdrlen;
	if ((v->encodebuf = kmalloc(maxsize, GFP_ATOMIC)) == NULL) {
		kfree(v);
		return NULL;
	}
	return v;
}
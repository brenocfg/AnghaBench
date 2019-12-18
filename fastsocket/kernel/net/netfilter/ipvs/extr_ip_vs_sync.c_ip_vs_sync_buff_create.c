#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ip_vs_sync_mesg {int dummy; } ;
struct ip_vs_sync_buff {unsigned char* head; unsigned char* end; int /*<<< orphan*/  firstuse; TYPE_1__* mesg; } ;
struct TYPE_2__ {int size; scalar_t__ spare; scalar_t__ nr_conns; int /*<<< orphan*/  syncid; int /*<<< orphan*/  version; scalar_t__ reserved; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SYNC_PROTO_VER ; 
 int /*<<< orphan*/  ip_vs_master_syncid ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct ip_vs_sync_buff*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int sync_send_mesg_maxlen ; 

__attribute__((used)) static inline struct ip_vs_sync_buff * ip_vs_sync_buff_create(void)
{
	struct ip_vs_sync_buff *sb;

	if (!(sb=kmalloc(sizeof(struct ip_vs_sync_buff), GFP_ATOMIC)))
		return NULL;

	if (!(sb->mesg=kmalloc(sync_send_mesg_maxlen, GFP_ATOMIC))) {
		kfree(sb);
		return NULL;
	}
	sb->mesg->reserved = 0;  /* old nr_conns i.e. must be zeo now */
	sb->mesg->version = SYNC_PROTO_VER;
	sb->mesg->syncid = ip_vs_master_syncid;
	sb->mesg->size = sizeof(struct ip_vs_sync_mesg);
	sb->mesg->nr_conns = 0;
	sb->mesg->spare = 0;
	sb->head = (unsigned char *)sb->mesg + sizeof(struct ip_vs_sync_mesg);
	sb->end = (unsigned char *)sb->mesg + sync_send_mesg_maxlen;

	sb->firstuse = jiffies;
	return sb;
}
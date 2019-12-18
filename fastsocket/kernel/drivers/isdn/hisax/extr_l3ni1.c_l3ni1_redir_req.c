#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct sk_buff {int dummy; } ;
struct TYPE_7__ {int invoke_id; int /*<<< orphan*/  uus1_data; } ;
struct TYPE_8__ {TYPE_2__ ni1; } ;
struct TYPE_6__ {int cause; } ;
struct l3_process {int /*<<< orphan*/  st; TYPE_5__* chan; TYPE_3__ prot; int /*<<< orphan*/  callref; TYPE_1__ para; } ;
struct TYPE_9__ {char* phone; int /*<<< orphan*/  screen; int /*<<< orphan*/  eazmsn; } ;
struct TYPE_10__ {TYPE_4__ setup; } ;

/* Variables and functions */
 int DL_DATA ; 
 int /*<<< orphan*/  MT_FACILITY ; 
 int /*<<< orphan*/  MsgHead (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REQUEST ; 
 int /*<<< orphan*/  free_invoke_id (int /*<<< orphan*/ ,int) ; 
 struct sk_buff* l3_alloc_skb (int) ; 
 int /*<<< orphan*/  l3_msg (int /*<<< orphan*/ ,int,struct sk_buff*) ; 
 int /*<<< orphan*/  l3ni1_disconnect_req (struct l3_process*,char,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int new_invoke_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char strlen (char*) ; 

__attribute__((used)) static void l3ni1_redir_req(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb;
	u_char tmp[128];
	u_char *p = tmp;
        u_char *subp;
        u_char len_phone = 0;
        u_char len_sub = 0;
	int l; 


        strcpy(pc->prot.ni1.uus1_data,pc->chan->setup.eazmsn); /* copy uus element if available */
        if (!pc->chan->setup.phone[0])
          { pc->para.cause = -1;
            l3ni1_disconnect_req(pc,pr,arg); /* disconnect immediately */
            return;
          } /* only uus */
 
        if (pc->prot.ni1.invoke_id) 
          free_invoke_id(pc->st,pc->prot.ni1.invoke_id);
 
        if (!(pc->prot.ni1.invoke_id = new_invoke_id(pc->st))) 
          return;

        MsgHead(p, pc->callref, MT_FACILITY);

        for (subp = pc->chan->setup.phone; (*subp) && (*subp != '.'); subp++) len_phone++; /* len of phone number */
        if (*subp++ == '.') len_sub = strlen(subp) + 2; /* length including info subaddress element */ 

	*p++ = 0x1c;   /* Facility info element */
        *p++ = len_phone + len_sub + 2 + 2 + 8 + 3 + 3; /* length of element */
        *p++ = 0x91;  /* remote operations protocol */
        *p++ = 0xa1;  /* invoke component */
	  
        *p++ = len_phone + len_sub + 2 + 2 + 8 + 3; /* length of data */
        *p++ = 0x02;  /* invoke id tag, integer */
	*p++ = 0x01;  /* length */
        *p++ = pc->prot.ni1.invoke_id;  /* invoke id */ 
        *p++ = 0x02;  /* operation value tag, integer */
	*p++ = 0x01;  /* length */
        *p++ = 0x0D;  /* Call Deflect */
	  
        *p++ = 0x30;  /* sequence phone number */
        *p++ = len_phone + 2 + 2 + 3 + len_sub; /* length */
	  
        *p++ = 0x30;  /* Deflected to UserNumber */
        *p++ = len_phone+2+len_sub; /* length */
        *p++ = 0x80; /* NumberDigits */
	*p++ = len_phone; /* length */
        for (l = 0; l < len_phone; l++)
	 *p++ = pc->chan->setup.phone[l];

        if (len_sub)
	  { *p++ = 0x04; /* called party subaddress */
            *p++ = len_sub - 2;
            while (*subp) *p++ = *subp++;
          }

        *p++ = 0x01; /* screening identifier */
        *p++ = 0x01;
        *p++ = pc->chan->setup.screen;

	l = p - tmp;
	if (!(skb = l3_alloc_skb(l))) return;
	memcpy(skb_put(skb, l), tmp, l);

        l3_msg(pc->st, DL_DATA | REQUEST, skb);
}
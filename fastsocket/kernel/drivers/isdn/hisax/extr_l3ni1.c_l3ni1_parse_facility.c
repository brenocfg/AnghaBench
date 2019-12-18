#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
typedef  int u_char ;
struct TYPE_5__ {int invoke_id; int remote_result; } ;
struct TYPE_6__ {TYPE_2__ ni1; } ;
struct l3_process {int redir_result; TYPE_3__ prot; struct PStack* st; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* l3l4 ) (struct PStack*,int,struct l3_process*) ;} ;
struct PStack {TYPE_1__ l3; } ;

/* Variables and functions */
 int CC_REDIR ; 
 int INDICATION ; 
 int /*<<< orphan*/  free_invoke_id (struct PStack*,int) ; 
 int /*<<< orphan*/  l3_debug (struct PStack*,char*,...) ; 
 int /*<<< orphan*/  l3ni1_dummy_error_return (struct PStack*,int,int) ; 
 int /*<<< orphan*/  l3ni1_dummy_invoke (struct PStack*,int,int,int,int*,unsigned char) ; 
 int /*<<< orphan*/  l3ni1_dummy_return_result (struct PStack*,int,int*,unsigned char) ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,struct l3_process*) ; 
 int /*<<< orphan*/  stub2 (struct PStack*,int,struct l3_process*) ; 

__attribute__((used)) static void
l3ni1_parse_facility(struct PStack *st, struct l3_process *pc,
                      int cr, u_char * p)
{
	int qd_len = 0;
	unsigned char nlen = 0, ilen, cp_tag;
	int ident, id;
	ulong err_ret;

	if (pc) 
		st = pc->st; /* valid Stack */
	else
		if ((!st) || (cr >= 0)) return; /* neither pc nor st specified */

	p++;
	qd_len = *p++;
	if (qd_len == 0) {
		l3_debug(st, "qd_len == 0");
		return;
	}
	if ((*p & 0x1F) != 0x11) {	/* Service discriminator, supplementary service */
		l3_debug(st, "supplementary service != 0x11");
		return;
	}
	while (qd_len > 0 && !(*p & 0x80)) {	/* extension ? */
		p++;
		qd_len--;
	}
	if (qd_len < 2) {
		l3_debug(st, "qd_len < 2");
		return;
	}
	p++;
	qd_len--;
	if ((*p & 0xE0) != 0xA0) {	/* class and form */
		l3_debug(st, "class and form != 0xA0");
		return;
	}
       
        cp_tag = *p & 0x1F; /* remember tag value */

        p++;
	qd_len--;
	if (qd_len < 1) 
          { l3_debug(st, "qd_len < 1");
	    return;
	  }
	if (*p & 0x80) 
          { /* length format indefinite or limited */
	    nlen = *p++ & 0x7F; /* number of len bytes or indefinite */
            if ((qd_len-- < ((!nlen) ? 3 : (1 + nlen))) ||
                (nlen > 1))   
	     { l3_debug(st, "length format error or not implemented");
	       return;
             }
            if (nlen == 1)
	     { nlen = *p++; /* complete length */
               qd_len--;
             } 
            else
	     { qd_len -= 2; /* trailing null bytes */
               if ((*(p+qd_len)) || (*(p+qd_len+1)))
		{ l3_debug(st,"length format indefinite error");
                  return;
                }
               nlen = qd_len;
             }
	  }
        else
	  { nlen = *p++;
	    qd_len--;
          } 
	if (qd_len < nlen) 
          { l3_debug(st, "qd_len < nlen");
	    return;
	  }
	qd_len -= nlen;

	if (nlen < 2) 
          { l3_debug(st, "nlen < 2");
	    return;
	  }
        if (*p != 0x02) 
          {  /* invoke identifier tag */
	     l3_debug(st, "invoke identifier tag !=0x02");
	     return;
	  }
	p++;
	nlen--;
	if (*p & 0x80) 
          { /* length format */
	    l3_debug(st, "invoke id length format 2");
	    return;
	  }
	ilen = *p++;
	nlen--;
	if (ilen > nlen || ilen == 0) 
          { l3_debug(st, "ilen > nlen || ilen == 0");
	    return;
	  }
	nlen -= ilen;
	id = 0;
	while (ilen > 0) 
          { id = (id << 8) | (*p++ & 0xFF);	/* invoke identifier */
	    ilen--;
	  }

	switch (cp_tag) {	/* component tag */
		case 1:	/* invoke */
				if (nlen < 2) {
					l3_debug(st, "nlen < 2 22");
					return;
				}
				if (*p != 0x02) {	/* operation value */
					l3_debug(st, "operation value !=0x02");
					return;
				}
				p++;
				nlen--;
				ilen = *p++;
				nlen--;
				if (ilen > nlen || ilen == 0) {
					l3_debug(st, "ilen > nlen || ilen == 0 22");
					return;
				}
				nlen -= ilen;
				ident = 0;
				while (ilen > 0) {
					ident = (ident << 8) | (*p++ & 0xFF);
					ilen--;
				}

				if (!pc) 
				{
					l3ni1_dummy_invoke(st, cr, id, ident, p, nlen);
					return;
				} 
				l3_debug(st, "invoke break");
				break;
		case 2:	/* return result */
			 /* if no process available handle separately */ 
                        if (!pc)
			 { if (cr == -1) 
                             l3ni1_dummy_return_result(st, id, p, nlen);
                           return; 
                         }   
                        if ((pc->prot.ni1.invoke_id) && (pc->prot.ni1.invoke_id == id))
                          { /* Diversion successful */
                            free_invoke_id(st,pc->prot.ni1.invoke_id);
                            pc->prot.ni1.remote_result = 0; /* success */     
                            pc->prot.ni1.invoke_id = 0;
                            pc->redir_result = pc->prot.ni1.remote_result; 
                            st->l3.l3l4(st, CC_REDIR | INDICATION, pc);                                  } /* Diversion successful */
                        else
                          l3_debug(st,"return error unknown identifier");
			break;
		case 3:	/* return error */
                            err_ret = 0;
	                    if (nlen < 2) 
                              { l3_debug(st, "return error nlen < 2");
	                        return;
	                      }
                            if (*p != 0x02) 
                              { /* result tag */
	                        l3_debug(st, "invoke error tag !=0x02");
	                        return;
	                      }
	                    p++;
	                    nlen--;
	                    if (*p > 4) 
                              { /* length format */
	                        l3_debug(st, "invoke return errlen > 4 ");
	                        return;
	                      }
	                    ilen = *p++;
	                    nlen--;
	                    if (ilen > nlen || ilen == 0) 
                              { l3_debug(st, "error return ilen > nlen || ilen == 0");
	                        return;
	                       }
	                    nlen -= ilen;
	                    while (ilen > 0) 
                             { err_ret = (err_ret << 8) | (*p++ & 0xFF);	/* error value */
	                       ilen--;
	                     }
			 /* if no process available handle separately */ 
                        if (!pc)
			 { if (cr == -1)
                             l3ni1_dummy_error_return(st, id, err_ret);
                           return; 
                         }   
                        if ((pc->prot.ni1.invoke_id) && (pc->prot.ni1.invoke_id == id))
                          { /* Deflection error */
                            free_invoke_id(st,pc->prot.ni1.invoke_id);
                            pc->prot.ni1.remote_result = err_ret; /* result */
                            pc->prot.ni1.invoke_id = 0; 
                            pc->redir_result = pc->prot.ni1.remote_result; 
                            st->l3.l3l4(st, CC_REDIR | INDICATION, pc);  
                          } /* Deflection error */
                        else
                          l3_debug(st,"return result unknown identifier");
			break;
		default:
			l3_debug(st, "facility default break tag=0x%02x",cp_tag);
			break;
	}
}
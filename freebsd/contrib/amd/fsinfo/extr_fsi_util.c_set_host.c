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
struct TYPE_5__ {int /*<<< orphan*/  q_back; } ;
typedef  TYPE_1__ qelem ;
struct TYPE_6__ {int h_mask; char* h_hostname; char* h_lochost; char* h_arch; char* h_os; char* h_cluster; TYPE_1__* h_ether; TYPE_1__* h_config; } ;
typedef  TYPE_2__ host ;
typedef  int /*<<< orphan*/  dict_ent ;

/* Variables and functions */
#define  HF_ARCH 133 
#define  HF_CLUSTER 132 
#define  HF_CONFIG 131 
#define  HF_ETHER 130 
#define  HF_HOST 129 
#define  HF_OS 128 
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  dict_add (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * dict_locate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dict_of_hosts ; 
 int /*<<< orphan*/  domain_strip (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_error (char*,char*) ; 
 char** host_strings ; 
 int /*<<< orphan*/  hostname ; 
 int /*<<< orphan*/  ins_que (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* new_que () ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 char* xstrdup (char*) ; 

void
set_host(host *hp, int k, char *v)
{
  int m = 1 << k;

  if (hp->h_mask & m) {
    fsi_error("host field \"%s\" already set", host_strings[k]);
    return;
  }
  hp->h_mask |= m;

  switch (k) {

  case HF_HOST:{
      char *p = xstrdup(v);
      dict_ent *de = dict_locate(dict_of_hosts, v);

      if (de)
	fsi_error("duplicate host %s!", v);
      else
	dict_add(dict_of_hosts, v, (char *) hp);
      hp->h_hostname = v;
      domain_strip(p, hostname);
      if (strchr(p, '.') != 0)
	XFREE(p);
      else
	hp->h_lochost = p;
    }
    break;

  case HF_CONFIG:{
      qelem *q;
      qelem *vq = (qelem *) v;

      hp->h_mask &= ~m;
      if (hp->h_config)
	q = hp->h_config;
      else
	q = hp->h_config = new_que();
      ins_que(vq, q->q_back);
    }
    break;

  case HF_ETHER:{
      qelem *q;
      qelem *vq = (qelem *) v;

      hp->h_mask &= ~m;
      if (hp->h_ether)
	q = hp->h_ether;
      else
	q = hp->h_ether = new_que();
      ins_que(vq, q->q_back);
    }
    break;

  case HF_ARCH:
    hp->h_arch = v;
    break;

  case HF_OS:
    hp->h_os = v;
    break;

  case HF_CLUSTER:
    hp->h_cluster = v;
    break;

  default:
    abort();
    break;
  }
}
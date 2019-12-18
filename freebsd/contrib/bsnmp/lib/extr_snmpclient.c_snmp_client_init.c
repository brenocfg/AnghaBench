#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int max_msg_size; } ;
struct TYPE_3__ {int tv_sec; scalar_t__ tv_usec; } ;
struct snmp_client {int retries; int txbuflen; int rxbuflen; int fd; TYPE_2__ engine; scalar_t__ next_reqid; scalar_t__ min_reqid; int /*<<< orphan*/  max_reqid; scalar_t__ dump_pdus; TYPE_1__ timeout; int /*<<< orphan*/  cname; int /*<<< orphan*/  security_model; int /*<<< orphan*/  write_community; int /*<<< orphan*/  read_community; int /*<<< orphan*/ * cport; int /*<<< orphan*/ * chost; int /*<<< orphan*/  trans; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT32_MAX ; 
 int /*<<< orphan*/  SNMP_SECMODEL_USM ; 
 int /*<<< orphan*/  SNMP_TRANS_UDP ; 
 int /*<<< orphan*/  SNMP_V2c ; 
 int /*<<< orphan*/  memset (struct snmp_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void
snmp_client_init(struct snmp_client *c)
{
	memset(c, 0, sizeof(*c));

	c->version = SNMP_V2c;
	c->trans = SNMP_TRANS_UDP;
	c->chost = NULL;
	c->cport = NULL;

	strcpy(c->read_community, "public");
	strcpy(c->write_community, "private");

	c->security_model = SNMP_SECMODEL_USM;
	strcpy(c->cname, "");

	c->timeout.tv_sec = 3;
	c->timeout.tv_usec = 0;
	c->retries = 3;
	c->dump_pdus = 0;
	c->txbuflen = c->rxbuflen = 10000;

	c->fd = -1;

	c->max_reqid = INT32_MAX;
	c->min_reqid = 0;
	c->next_reqid = 0;

	c->engine.max_msg_size = 1500; /* XXX */
}
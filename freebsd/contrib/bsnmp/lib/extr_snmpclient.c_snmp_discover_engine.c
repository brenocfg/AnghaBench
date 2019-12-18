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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ engine_boots; scalar_t__ engine_time; scalar_t__ engine_len; int /*<<< orphan*/  engine_id; int /*<<< orphan*/  max_msg_size; } ;
struct snmp_pdu {scalar_t__ version; scalar_t__ error_status; TYPE_2__ engine; } ;
typedef  enum snmp_privacy { ____Placeholder_snmp_privacy } snmp_privacy ;
typedef  enum snmp_authentication { ____Placeholder_snmp_authentication } snmp_authentication ;
typedef  int /*<<< orphan*/  cname ;
struct TYPE_7__ {scalar_t__ engine_boots; scalar_t__ engine_time; scalar_t__ engine_len; int /*<<< orphan*/  engine_id; int /*<<< orphan*/  max_msg_size; } ;
struct TYPE_9__ {char* sec_name; int auth_proto; int priv_proto; } ;
struct TYPE_10__ {scalar_t__ version; TYPE_1__ engine; TYPE_3__ user; } ;

/* Variables and functions */
 int SNMP_ADM_STR32_SIZ ; 
 scalar_t__ SNMP_AUTH_NOAUTH ; 
 scalar_t__ SNMP_CODE_OK ; 
 scalar_t__ SNMP_ERR_NOERROR ; 
 int /*<<< orphan*/  SNMP_PDU_GET ; 
 int SNMP_PRIV_NOPRIV ; 
 scalar_t__ SNMP_V3 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seterr (TYPE_5__*,char*,...) ; 
 TYPE_5__ snmp_client ; 
 int snmp_dialog (struct snmp_pdu*,struct snmp_pdu*) ; 
 scalar_t__ snmp_get_local_keys (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ snmp_passwd_to_keys (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  snmp_pdu_create (struct snmp_pdu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_pdu_free (struct snmp_pdu*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

int
snmp_discover_engine(char *passwd)
{
	char cname[SNMP_ADM_STR32_SIZ];
	enum snmp_authentication cap;
	enum snmp_privacy cpp;
	struct snmp_pdu req, resp;

	if (snmp_client.version != SNMP_V3)
		seterr(&snmp_client, "wrong version");

	strlcpy(cname, snmp_client.user.sec_name, sizeof(cname));
	cap = snmp_client.user.auth_proto;
	cpp = snmp_client.user.priv_proto;

	snmp_client.engine.engine_len = 0;
	snmp_client.engine.engine_boots = 0;
	snmp_client.engine.engine_time = 0;
	snmp_client.user.auth_proto = SNMP_AUTH_NOAUTH;
	snmp_client.user.priv_proto = SNMP_PRIV_NOPRIV;
	memset(snmp_client.user.sec_name, 0, sizeof(snmp_client.user.sec_name));

	snmp_pdu_create(&req, SNMP_PDU_GET);

	if (snmp_dialog(&req, &resp) == -1)
		 return (-1);

	if (resp.version != req.version) {
		seterr(&snmp_client, "wrong version");
		return (-1);
	}

	if (resp.error_status != SNMP_ERR_NOERROR) {
		seterr(&snmp_client, "Error %d in responce", resp.error_status);
		return (-1);
	}

	snmp_client.engine.engine_len = resp.engine.engine_len;
	snmp_client.engine.max_msg_size = resp.engine.max_msg_size;
	memcpy(snmp_client.engine.engine_id, resp.engine.engine_id,
	    resp.engine.engine_len);

	strlcpy(snmp_client.user.sec_name, cname,
	    sizeof(snmp_client.user.sec_name));
	snmp_client.user.auth_proto = cap;
	snmp_client.user.priv_proto = cpp;

	if (snmp_client.user.auth_proto == SNMP_AUTH_NOAUTH)
		return (0);

	if (passwd == NULL ||
	    snmp_passwd_to_keys(&snmp_client.user, passwd) != SNMP_CODE_OK ||
	    snmp_get_local_keys(&snmp_client.user, snmp_client.engine.engine_id,
	    snmp_client.engine.engine_len) != SNMP_CODE_OK)
		return (-1);

	if (resp.engine.engine_boots != 0)
		snmp_client.engine.engine_boots = resp.engine.engine_boots;

	if (resp.engine.engine_time != 0) {
		snmp_client.engine.engine_time = resp.engine.engine_time;
		return (0);
	}

	snmp_pdu_free(&req);

	snmp_pdu_create(&req, SNMP_PDU_GET);
	req.engine.engine_boots = 0;
	req.engine.engine_time = 0;

	if (snmp_dialog(&req, &resp) == -1)
		return (-1);

	if (resp.version != req.version) {
		seterr(&snmp_client, "wrong version");
		return (-1);
	}

	if (resp.error_status != SNMP_ERR_NOERROR) {
		seterr(&snmp_client, "Error %d in responce", resp.error_status);
		return (-1);
	}

	snmp_client.engine.engine_boots = resp.engine.engine_boots;
	snmp_client.engine.engine_time = resp.engine.engine_time;

	snmp_pdu_free(&req);
	snmp_pdu_free(&resp);

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_18__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; scalar_t__ tm_year; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; } ;
struct TYPE_30__ {TYPE_7__* server; TYPE_3__* client; } ;
typedef  TYPE_9__ network_mysqld_con ;
struct TYPE_25__ {scalar_t__ query_status; } ;
struct TYPE_19__ {double ts_read_query_result_last; double ts_read_query; TYPE_8__* query; TYPE_4__ qstat; } ;
typedef  TYPE_10__ injection ;
typedef  scalar_t__ gint ;
struct TYPE_29__ {scalar_t__ str; } ;
struct TYPE_28__ {TYPE_6__* dst; } ;
struct TYPE_27__ {TYPE_5__* name; } ;
struct TYPE_26__ {int /*<<< orphan*/  str; } ;
struct TYPE_24__ {TYPE_2__* src; } ;
struct TYPE_23__ {TYPE_1__* name; } ;
struct TYPE_22__ {int /*<<< orphan*/  str; } ;
struct TYPE_21__ {scalar_t__ sql_log_slow_ms; int /*<<< orphan*/  sql_log; } ;
struct TYPE_20__ {int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;
typedef  TYPE_11__ GString ;

/* Variables and functions */
 scalar_t__ MYSQLD_PACKET_OK ; 
 scalar_t__ OFF ; 
 scalar_t__ REALTIME ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_18__* config ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_append_printf (TYPE_11__*,char*,int /*<<< orphan*/ ,float,scalar_t__) ; 
 int /*<<< orphan*/  g_string_free (TYPE_11__*,int /*<<< orphan*/ ) ; 
 TYPE_11__* g_string_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_string_printf (TYPE_11__*,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 scalar_t__ sql_log_type ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void log_sql(network_mysqld_con* con, injection* inj) {
	if (sql_log_type == OFF) return;
	
	float latency_ms = (inj->ts_read_query_result_last - inj->ts_read_query)/1000.0;
	if ((gint)latency_ms < config->sql_log_slow_ms) return;

	GString* message = g_string_new(NULL);

	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	g_string_printf(message, "[%02d/%02d/%d %02d:%02d:%02d] C:%s S:", tm->tm_mon+1, tm->tm_mday, tm->tm_year+1900, tm->tm_hour, tm->tm_min, tm->tm_sec, con->client->src->name->str);

	if (inj->qstat.query_status == MYSQLD_PACKET_OK) {
		g_string_append_printf(message, "%s OK %.3f \"%s\"\n", con->server->dst->name->str, latency_ms, inj->query->str+1);
	} else {
		g_string_append_printf(message, "%s ERR %.3f \"%s\"\n", con->server->dst->name->str, latency_ms, inj->query->str+1);
	}

	fwrite(message->str, message->len, 1, config->sql_log);
	g_string_free(message, TRUE);

	if (sql_log_type == REALTIME) fflush(config->sql_log);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int format; scalar_t__ summary; scalar_t__ timing; scalar_t__ buffers; scalar_t__ costs; scalar_t__ verbose; scalar_t__ analyze; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ ExplainState ;

/* Variables and functions */
#define  EXPLAIN_FORMAT_JSON 130 
#define  EXPLAIN_FORMAT_XML 129 
#define  EXPLAIN_FORMAT_YAML 128 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  makeStringInfo () ; 

__attribute__((used)) static StringInfo
BuildRemoteExplainQuery(char *queryString, ExplainState *es)
{
	StringInfo explainQuery = makeStringInfo();
	char *formatStr = NULL;

	switch (es->format)
	{
		case EXPLAIN_FORMAT_XML:
		{
			formatStr = "XML";
			break;
		}

		case EXPLAIN_FORMAT_JSON:
		{
			formatStr = "JSON";
			break;
		}

		case EXPLAIN_FORMAT_YAML:
		{
			formatStr = "YAML";
			break;
		}

		default:
		{
			formatStr = "TEXT";
			break;
		}
	}

	appendStringInfo(explainQuery,
					 "EXPLAIN (ANALYZE %s, VERBOSE %s, "
					 "COSTS %s, BUFFERS %s, TIMING %s, SUMMARY %s, "
					 "FORMAT %s) %s",
					 es->analyze ? "TRUE" : "FALSE",
					 es->verbose ? "TRUE" : "FALSE",
					 es->costs ? "TRUE" : "FALSE",
					 es->buffers ? "TRUE" : "FALSE",
					 es->timing ? "TRUE" : "FALSE",
					 es->summary ? "TRUE" : "FALSE",
					 formatStr,
					 queryString);

	return explainQuery;
}
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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {char* string; } ;
typedef  TYPE_1__ pc_token_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_2__ keywordHash_t ;
typedef  int /*<<< orphan*/  itemDef_t ;

/* Variables and functions */
 TYPE_2__* KeywordHash_Find (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PC_SourceError (int,char*,...) ; 
 int /*<<< orphan*/  itemParseKeywordHash ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trap_PC_ReadToken (int,TYPE_1__*) ; 

qboolean Item_Parse(int handle, itemDef_t *item) {
	pc_token_t token;
	keywordHash_t *key;


	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;
	if (*token.string != '{') {
		return qfalse;
	}
	while ( 1 ) {
		if (!trap_PC_ReadToken(handle, &token)) {
			PC_SourceError(handle, "end of file inside menu item\n");
			return qfalse;
		}

		if (*token.string == '}') {
			return qtrue;
		}

		key = KeywordHash_Find(itemParseKeywordHash, token.string);
		if (!key) {
			PC_SourceError(handle, "unknown menu item keyword %s", token.string);
			continue;
		}
		if ( !key->func(item, handle) ) {
			PC_SourceError(handle, "couldn't parse menu item keyword %s", token.string);
			return qfalse;
		}
	}
	return qfalse; 	// bk001205 - LCC missing return value
}
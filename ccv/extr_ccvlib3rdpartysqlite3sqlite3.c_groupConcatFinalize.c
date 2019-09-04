#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_4__ {scalar_t__ accError; } ;
typedef  TYPE_1__ StrAccum ;

/* Variables and functions */
 scalar_t__ STRACCUM_NOMEM ; 
 scalar_t__ STRACCUM_TOOBIG ; 
 int /*<<< orphan*/  sqlite3StrAccumFinish (TYPE_1__*) ; 
 TYPE_1__* sqlite3_aggregate_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_error_toobig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void groupConcatFinalize(sqlite3_context *context){
  StrAccum *pAccum;
  pAccum = sqlite3_aggregate_context(context, 0);
  if( pAccum ){
    if( pAccum->accError==STRACCUM_TOOBIG ){
      sqlite3_result_error_toobig(context);
    }else if( pAccum->accError==STRACCUM_NOMEM ){
      sqlite3_result_error_nomem(context);
    }else{    
      sqlite3_result_text(context, sqlite3StrAccumFinish(pAccum), -1, 
                          sqlite3_free);
    }
  }
}
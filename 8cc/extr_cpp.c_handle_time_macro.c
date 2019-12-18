#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  Token ;

/* Variables and functions */
 int /*<<< orphan*/  TSTRING ; 
 int /*<<< orphan*/  make_token_pushback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_time_macro(Token *tmpl) {
    char buf[10];
    strftime(buf, sizeof(buf), "%T", &now);
    make_token_pushback(tmpl, TSTRING, strdup(buf));
}
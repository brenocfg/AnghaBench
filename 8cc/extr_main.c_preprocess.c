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
struct TYPE_4__ {scalar_t__ kind; scalar_t__ space; scalar_t__ bol; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 scalar_t__ TEOF ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* read_token () ; 
 char* tok2s (TYPE_1__*) ; 

__attribute__((used)) static void preprocess() {
    for (;;) {
        Token *tok = read_token();
        if (tok->kind == TEOF)
            break;
        if (tok->bol)
            printf("\n");
        if (tok->space)
            printf(" ");
        printf("%s", tok2s(tok));
    }
    printf("\n");
    exit(0);
}
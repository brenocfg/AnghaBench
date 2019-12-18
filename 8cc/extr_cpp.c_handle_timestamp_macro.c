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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {TYPE_1__* file; } ;
typedef  TYPE_2__ Token ;
struct TYPE_5__ {int /*<<< orphan*/  mtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSTRING ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_token_pushback (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_timestamp_macro(Token *tmpl) {
    // [GNU] __TIMESTAMP__ is expanded to a string that describes the date
    // and time of the last modification time of the current source file.
    char buf[30];
    strftime(buf, sizeof(buf), "%a %b %e %T %Y", localtime(&tmpl->file->mtime));
    make_token_pushback(tmpl, TSTRING, strdup(buf));
}
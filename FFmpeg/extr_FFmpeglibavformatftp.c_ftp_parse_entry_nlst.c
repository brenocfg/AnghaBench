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
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ AVIODirEntry ;

/* Variables and functions */
 int /*<<< orphan*/  av_strdup (char*) ; 

__attribute__((used)) static int ftp_parse_entry_nlst(char *line, AVIODirEntry *next)
{
    next->name = av_strdup(line);
    return 0;
}
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
struct TYPE_3__ {int /*<<< orphan*/  size; void* group_id; void* user_id; void* filemode; int /*<<< orphan*/  modification_timestamp; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ AVIODirEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_ENTRY_DIRECTORY ; 
 int /*<<< orphan*/  AVIO_ENTRY_FILE ; 
 int /*<<< orphan*/  AVIO_ENTRY_SYMBOLIC_LINK ; 
 int /*<<< orphan*/  av_strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  av_strdup (char*) ; 
 char* av_strtok (char*,char*,char**) ; 
 int /*<<< orphan*/  ff_dlog (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  ftp_parse_date (char*) ; 
 int /*<<< orphan*/  strtoll (char*,int /*<<< orphan*/ *,int) ; 
 void* strtoumax (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ftp_parse_entry_mlsd(char *mlsd, AVIODirEntry *next)
{
    char *fact, *value;
    ff_dlog(NULL, "%s\n", mlsd);
    while(fact = av_strtok(mlsd, ";", &mlsd)) {
        if (fact[0] == ' ') {
            next->name = av_strdup(&fact[1]);
            continue;
        }
        fact = av_strtok(fact, "=", &value);
        if (!av_strcasecmp(fact, "type")) {
            if (!av_strcasecmp(value, "cdir") || !av_strcasecmp(value, "pdir"))
                return 1;
            if (!av_strcasecmp(value, "dir"))
                next->type = AVIO_ENTRY_DIRECTORY;
            else if (!av_strcasecmp(value, "file"))
                next->type = AVIO_ENTRY_FILE;
            else if (!av_strcasecmp(value, "OS.unix=slink:"))
                next->type = AVIO_ENTRY_SYMBOLIC_LINK;
        } else if (!av_strcasecmp(fact, "modify")) {
            next->modification_timestamp = ftp_parse_date(value);
        } else if (!av_strcasecmp(fact, "UNIX.mode")) {
            next->filemode = strtoumax(value, NULL, 8);
        } else if (!av_strcasecmp(fact, "UNIX.uid") || !av_strcasecmp(fact, "UNIX.owner"))
            next->user_id = strtoumax(value, NULL, 10);
        else if (!av_strcasecmp(fact, "UNIX.gid") || !av_strcasecmp(fact, "UNIX.group"))
            next->group_id = strtoumax(value, NULL, 10);
        else if (!av_strcasecmp(fact, "size") || !av_strcasecmp(fact, "sizd"))
            next->size = strtoll(value, NULL, 10);
    }
    return 0;
}
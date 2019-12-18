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

/* Variables and functions */
 int /*<<< orphan*/  hb_community ; 
 int /*<<< orphan*/  hb_irc ; 
 int /*<<< orphan*/  hb_repo_branch ; 
 int /*<<< orphan*/  hb_repo_hash ; 
 int /*<<< orphan*/  hb_repo_remote ; 
 int /*<<< orphan*/  hb_repo_rev ; 
 int /*<<< orphan*/  hb_repo_tag ; 
 int /*<<< orphan*/  hb_repo_type ; 
 int /*<<< orphan*/  hb_repo_url ; 
 char* hb_strdup_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_title ; 
 int /*<<< orphan*/  hb_website ; 

const char * hb_get_full_description()
{
    static char * desc = NULL;
    if (desc == NULL)
    {
        desc = hb_strdup_printf("%s\n"
                                "\tWebsite:     %s\n"
                                "\tForum:       %s\n"
                                "\tIRC:         %s\n"
                                "\tBuild Type:  %s\n"
                                "\tRepository:  %s\n"
                                "\tRelease Tag: %s\n"
                                "\tRevision:    %d\n"
                                "\tCommit Hash: %s\n"
                                "\tBranch:      %s\n"
                                "\tRemote:      %s",
                                hb_title, hb_website, hb_community, hb_irc,
                                hb_repo_type, hb_repo_url, hb_repo_tag, hb_repo_rev,
                                hb_repo_hash, hb_repo_branch, hb_repo_remote);
    }
    return desc;
}
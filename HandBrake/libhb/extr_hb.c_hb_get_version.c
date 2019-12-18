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
typedef  int /*<<< orphan*/  hb_handle_t ;

/* Variables and functions */
 scalar_t__ hb_community ; 
 scalar_t__ hb_irc ; 
 scalar_t__ hb_name ; 
 scalar_t__ hb_repo_branch ; 
 scalar_t__ hb_repo_hash ; 
 scalar_t__ hb_repo_remote ; 
 scalar_t__ hb_repo_rev ; 
 scalar_t__ hb_repo_tag ; 
 scalar_t__ hb_repo_type ; 
 scalar_t__ hb_repo_url ; 
 scalar_t__ hb_title ; 
 char const* hb_version ; 
 scalar_t__ hb_website ; 

const char * hb_get_version( hb_handle_t * h )
{
    // Silence compiler warnings for unused variables
    ((void)(hb_title));
    ((void)(hb_name));
    ((void)(hb_website));
    ((void)(hb_community));
    ((void)(hb_irc));
    ((void)(hb_version));
    ((void)(hb_repo_url));
    ((void)(hb_repo_tag));
    ((void)(hb_repo_rev));
    ((void)(hb_repo_hash));
    ((void)(hb_repo_branch));
    ((void)(hb_repo_remote));
    ((void)(hb_repo_type));
    return hb_version;
}
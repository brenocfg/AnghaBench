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
struct cifs_tcon {scalar_t__ tidStatus; int /*<<< orphan*/  treeName; } ;

/* Variables and functions */
 scalar_t__ CifsExiting ; 
 int /*<<< orphan*/  MAX_TREE_SIZE ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_tcon(struct cifs_tcon *tcon, const char *unc)
{
	if (tcon->tidStatus == CifsExiting)
		return 0;
	if (strncmp(tcon->treeName, unc, MAX_TREE_SIZE))
		return 0;
	return 1;
}
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
typedef  int u32 ;
struct bearer_name {int /*<<< orphan*/  if_name; int /*<<< orphan*/  media_name; } ;

/* Variables and functions */
 int TIPC_MAX_BEARER_NAME ; 
 int TIPC_MAX_IF_NAME ; 
 int TIPC_MAX_MEDIA_NAME ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int strspn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_alphabet ; 

__attribute__((used)) static int bearer_name_validate(const char *name,
				struct bearer_name *name_parts)
{
	char name_copy[TIPC_MAX_BEARER_NAME];
	char *media_name;
	char *if_name;
	u32 media_len;
	u32 if_len;

	/* copy bearer name & ensure length is OK */

	name_copy[TIPC_MAX_BEARER_NAME - 1] = 0;
	/* need above in case non-Posix strncpy() doesn't pad with nulls */
	strncpy(name_copy, name, TIPC_MAX_BEARER_NAME);
	if (name_copy[TIPC_MAX_BEARER_NAME - 1] != 0)
		return 0;

	/* ensure all component parts of bearer name are present */

	media_name = name_copy;
	if ((if_name = strchr(media_name, ':')) == NULL)
		return 0;
	*(if_name++) = 0;
	media_len = if_name - media_name;
	if_len = strlen(if_name) + 1;

	/* validate component parts of bearer name */

	if ((media_len <= 1) || (media_len > TIPC_MAX_MEDIA_NAME) ||
	    (if_len <= 1) || (if_len > TIPC_MAX_IF_NAME) ||
	    (strspn(media_name, tipc_alphabet) != (media_len - 1)) ||
	    (strspn(if_name, tipc_alphabet) != (if_len - 1)))
		return 0;

	/* return bearer name components, if necessary */

	if (name_parts) {
		strcpy(name_parts->media_name, media_name);
		strcpy(name_parts->if_name, if_name);
	}
	return 1;
}
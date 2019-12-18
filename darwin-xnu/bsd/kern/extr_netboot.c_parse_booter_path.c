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
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int inet_aton (char*,struct in_addr*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static __inline__ boolean_t
parse_booter_path(char * path, struct in_addr * iaddr_p, char const * * host,
		  char * * mount_dir, char * * image_path)
{
    char *	start;
    char *	colon;

    /* IP address */
    start = path;
    colon = strchr(start, ':');
    if (colon == NULL) {
	return (FALSE);
    }
    *colon = '\0';
    if (inet_aton(start, iaddr_p) != 1) {
	return (FALSE);
    }

    /* host */
    start = colon + 1;
    colon = strchr(start, ':');
    if (colon == NULL) {
	return (FALSE);
    }
    *colon = '\0';
    *host = start;

    /* mount */
    start = colon + 1;
    colon = strchr(start, ':');
    *mount_dir = start;
    if (colon == NULL) {
	*image_path = NULL;
    }
    else {
	/* image path */
	*colon = '\0';
	start = colon + 1;
	*image_path = start;
    }
    return (TRUE);
}
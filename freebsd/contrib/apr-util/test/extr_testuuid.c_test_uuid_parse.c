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
typedef  int /*<<< orphan*/  uuid ;
typedef  int /*<<< orphan*/  apr_uuid_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_ASSERT (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  APR_UUID_FORMATTED_LENGTH ; 
 int /*<<< orphan*/  apr_uuid_format (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_uuid_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_uuid_parse (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_uuid_parse(abts_case *tc, void *data)
{
    apr_uuid_t uuid;
    apr_uuid_t uuid2;
    char buf[APR_UUID_FORMATTED_LENGTH + 1];

    apr_uuid_get(&uuid);
    apr_uuid_format(buf, &uuid);

    apr_uuid_parse(&uuid2, buf);
    ABTS_ASSERT(tc, "parse produced a different UUID",
             memcmp(&uuid, &uuid2, sizeof(uuid)) == 0);
}
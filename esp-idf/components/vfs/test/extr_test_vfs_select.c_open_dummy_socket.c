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
struct addrinfo {int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (struct addrinfo*) ; 
 int getaddrinfo (char*,char*,struct addrinfo const*,struct addrinfo**) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int open_dummy_socket(void)
{
    const struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_DGRAM,
    };
    struct addrinfo *res = NULL;

    const int err = getaddrinfo("localhost", "80", &hints, &res);
    TEST_ASSERT_EQUAL(0, err);
    TEST_ASSERT_NOT_NULL(res);

    const int dummy_socket_fd = socket(res->ai_family, res->ai_socktype, 0);
    TEST_ASSERT(dummy_socket_fd >= 0);

    return dummy_socket_fd;
}
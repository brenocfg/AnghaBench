#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  member_0; } ;
struct sockaddr {int dummy; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_MESSAGE (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (struct addrinfo*) ; 
 int bind (int,struct sockaddr*,int) ; 
 int connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char*,char*,struct addrinfo const*,struct addrinfo**) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int socket_init(void)
{
    const struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_DGRAM,
    };
    struct addrinfo *res;
    int err;
    struct sockaddr_in saddr = { 0 };
    int socket_fd = -1;

    err = getaddrinfo("localhost", "80", &hints, &res);
    TEST_ASSERT_EQUAL(err, 0);
    TEST_ASSERT_NOT_NULL(res);

    socket_fd = socket(res->ai_family, res->ai_socktype, 0);
    TEST_ASSERT(socket_fd >= 0);

    saddr.sin_family = PF_INET;
    saddr.sin_port = htons(80);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    err = bind(socket_fd, (struct sockaddr *) &saddr, sizeof(struct sockaddr_in));
    TEST_ASSERT(err >= 0);

    err = connect(socket_fd, res->ai_addr, res->ai_addrlen);
    TEST_ASSERT_EQUAL_MESSAGE(err, 0, "Socket connection failed");

    freeaddrinfo(res);

    return socket_fd;
}
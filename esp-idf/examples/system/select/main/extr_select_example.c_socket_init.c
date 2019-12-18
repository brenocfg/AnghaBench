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
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  TAG ; 
 int bind (scalar_t__,struct sockaddr*,int) ; 
 scalar_t__ connect (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  esp_netif_init () ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char*,char*,struct addrinfo const*,struct addrinfo**) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_deinit () ; 
 scalar_t__ socket_fd ; 

__attribute__((used)) static void socket_init(void)
{
    const struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_DGRAM,
    };
    struct addrinfo *res;
    int err;
    struct sockaddr_in saddr = { 0 };

    esp_netif_init();

    err = getaddrinfo("localhost", "80", &hints, &res);

    if (err != 0 || res == NULL) {
        ESP_LOGE(TAG, "DNS lookup failed: %d", errno);
        return;
    }

    socket_fd = socket(res->ai_family, res->ai_socktype, 0);

    if (socket_fd < 0) {
        ESP_LOGE(TAG, "Failed to allocate socket.");
        freeaddrinfo(res);
        return;
    }

    saddr.sin_family = PF_INET;
    saddr.sin_port = htons(80);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    err = bind(socket_fd, (struct sockaddr *) &saddr, sizeof(struct sockaddr_in));
    if (err < 0) {
        ESP_LOGE(TAG, "Failed to bind socket");
        freeaddrinfo(res);
        socket_deinit();
        return;
    }

    if (connect(socket_fd, res->ai_addr, res->ai_addrlen) != 0) {
        ESP_LOGE(TAG, "Socket connection failed: %d", errno);
        freeaddrinfo(res);
        socket_deinit();
        return;
    }

    freeaddrinfo(res);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fd; } ;
struct TYPE_3__ {scalar_t__ fd; } ;

/* Variables and functions */
 TYPE_2__ client ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 TYPE_1__ server ; 

void cleanup() {
  if (client.fd) {
    close(client.fd);
    client.fd = 0;
  }
  if (server.fd) {
    close(server.fd);
    server.fd = 0;
  }
}
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
struct http_parser_url {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct http_parser_url*,int /*<<< orphan*/ ,int) ; 

void
http_parser_url_init(struct http_parser_url *u) {
  memset(u, 0, sizeof(*u));
}
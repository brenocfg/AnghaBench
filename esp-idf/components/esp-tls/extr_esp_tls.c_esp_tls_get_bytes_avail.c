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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  esp_tls_t ;

/* Variables and functions */
 int /*<<< orphan*/  _esp_tls_get_bytes_avail (int /*<<< orphan*/ *) ; 

ssize_t esp_tls_get_bytes_avail(esp_tls_t *tls)
{
    return _esp_tls_get_bytes_avail(tls);
}
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

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  cli_handle ; 
 scalar_t__ isalpha (int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,...) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  xQueueSend (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enter_passkey_handler(int argc, char *argv[])
{
    int key;
    char pkey[8];
    int num;

    if (argc != 2) {
        return -1;
    }

    sscanf(argv[1], "%s", pkey);
    ESP_LOGI("You entered", "%s %s", argv[0], argv[1]);
    num = pkey[0];

    if (isalpha(num)) {
        if ((strcasecmp(pkey, "Y") == 0) || (strcasecmp(pkey, "Yes") == 0)) {
            key = 1;
            xQueueSend(cli_handle, &key, 0);
        } else {
            key = 0;
            xQueueSend(cli_handle, &key, 0);
        }
    } else {
        sscanf(pkey, "%d", &key);
        xQueueSend(cli_handle, &key, 0);
    }

    return 0;
}
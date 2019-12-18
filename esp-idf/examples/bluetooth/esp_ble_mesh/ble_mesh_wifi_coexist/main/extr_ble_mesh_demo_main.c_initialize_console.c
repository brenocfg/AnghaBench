#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  linenoiseHintsCallback ;
struct TYPE_3__ {int max_cmdline_args; int max_cmdline_length; int /*<<< orphan*/  hint_color; } ;
typedef  TYPE_1__ esp_console_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ESP_CONSOLE_UART_NUM ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LINE_ENDINGS_CR ; 
 int /*<<< orphan*/  ESP_LINE_ENDINGS_CRLF ; 
 int /*<<< orphan*/  LOG_COLOR_CYAN ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_console_get_completion ; 
 int /*<<< orphan*/  esp_console_get_hint ; 
 int /*<<< orphan*/  esp_console_init (TYPE_1__*) ; 
 int /*<<< orphan*/  esp_vfs_dev_uart_set_rx_line_endings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_vfs_dev_uart_set_tx_line_endings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_vfs_dev_uart_use_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linenoiseHistorySetMaxLen (int) ; 
 int /*<<< orphan*/  linenoiseSetCompletionCallback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linenoiseSetHintsCallback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linenoiseSetMultiLine (int) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  uart_driver_install (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void initialize_console(void)
{
    /* Disable buffering on stdin and stdout */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    /* Minicom, screen, idf_monitor send CR when ENTER key is pressed */
    esp_vfs_dev_uart_set_rx_line_endings(ESP_LINE_ENDINGS_CR);
    /* Move the caret to the beginning of the next line on '\n' */
    esp_vfs_dev_uart_set_tx_line_endings(ESP_LINE_ENDINGS_CRLF);

    /* Install UART driver for interrupt-driven reads and writes */
    ESP_ERROR_CHECK( uart_driver_install(CONFIG_ESP_CONSOLE_UART_NUM,
                                         256, 0, 0, NULL, 0) );

    /* Tell VFS to use UART driver */
    esp_vfs_dev_uart_use_driver(CONFIG_ESP_CONSOLE_UART_NUM);

    /* Initialize the console */
    esp_console_config_t console_config = {
        .max_cmdline_args = 32,
        .max_cmdline_length = 256,
#if CONFIG_LOG_COLORS
        .hint_color = atoi(LOG_COLOR_CYAN)
#endif
    };
    ESP_ERROR_CHECK( esp_console_init(&console_config) );

    /* Configure linenoise line completion library */
    /* Enable multiline editing. If not set, long commands will scroll within
     * single line.
     */
    linenoiseSetMultiLine(1);

    /* Tell linenoise where to get command completions and hints */
    linenoiseSetCompletionCallback(&esp_console_get_completion);
    linenoiseSetHintsCallback((linenoiseHintsCallback *) &esp_console_get_hint);

    /* Set command history size */
    linenoiseHistorySetMaxLen(100);
}
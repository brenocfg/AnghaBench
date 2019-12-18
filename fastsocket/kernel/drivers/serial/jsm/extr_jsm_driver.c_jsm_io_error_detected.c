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
struct pci_dev {int dummy; } ;
struct jsm_board {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  int /*<<< orphan*/  pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  jsm_remove_uart_port (struct jsm_board*) ; 
 struct jsm_board* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t jsm_io_error_detected(struct pci_dev *pdev,
					pci_channel_state_t state)
{
	struct jsm_board *brd = pci_get_drvdata(pdev);

	jsm_remove_uart_port(brd);

	return PCI_ERS_RESULT_NEED_RESET;
}
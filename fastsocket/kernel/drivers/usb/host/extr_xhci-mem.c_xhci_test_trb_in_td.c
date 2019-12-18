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
typedef  union xhci_trb {int dummy; } xhci_trb ;
struct xhci_segment {int dummy; } ;
struct xhci_hcd {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 struct xhci_segment* trb_in_td (struct xhci_segment*,union xhci_trb*,union xhci_trb*,scalar_t__) ; 
 unsigned long long xhci_trb_virt_to_dma (struct xhci_segment*,union xhci_trb*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,char*,int,...) ; 

__attribute__((used)) static int xhci_test_trb_in_td(struct xhci_hcd *xhci,
		struct xhci_segment *input_seg,
		union xhci_trb *start_trb,
		union xhci_trb *end_trb,
		dma_addr_t input_dma,
		struct xhci_segment *result_seg,
		char *test_name, int test_number)
{
	unsigned long long start_dma;
	unsigned long long end_dma;
	struct xhci_segment *seg;

	start_dma = xhci_trb_virt_to_dma(input_seg, start_trb);
	end_dma = xhci_trb_virt_to_dma(input_seg, end_trb);

	seg = trb_in_td(input_seg, start_trb, end_trb, input_dma);
	if (seg != result_seg) {
		xhci_warn(xhci, "WARN: %s TRB math test %d failed!\n",
				test_name, test_number);
		xhci_warn(xhci, "Tested TRB math w/ seg %p and "
				"input DMA 0x%llx\n",
				input_seg,
				(unsigned long long) input_dma);
		xhci_warn(xhci, "starting TRB %p (0x%llx DMA), "
				"ending TRB %p (0x%llx DMA)\n",
				start_trb, start_dma,
				end_trb, end_dma);
		xhci_warn(xhci, "Expected seg %p, got seg %p\n",
				result_seg, seg);
		return -1;
	}
	return 0;
}
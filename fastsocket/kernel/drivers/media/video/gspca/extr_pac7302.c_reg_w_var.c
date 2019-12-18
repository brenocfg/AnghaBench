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
struct gspca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int D_ERR ; 
 int D_STREAM ; 
#define  END_OF_SEQUENCE 129 
#define  LOAD_PAGE3 128 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int USB_BUF_SZ ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  reg_w_page (struct gspca_dev*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void reg_w_var(struct gspca_dev *gspca_dev,
			const __u8 *seq,
			const __u8 *page3, unsigned int page3_len)
{
	int index, len;

	for (;;) {
		index = *seq++;
		len = *seq++;
		switch (len) {
		case END_OF_SEQUENCE:
			return;
		case LOAD_PAGE3:
			reg_w_page(gspca_dev, page3, page3_len);
			break;
		default:
			if (len > USB_BUF_SZ) {
				PDEBUG(D_ERR|D_STREAM,
					"Incorrect variable sequence");
				return;
			}
			while (len > 0) {
				if (len < 8) {
					reg_w_buf(gspca_dev,
						index, seq, len);
					seq += len;
					break;
				}
				reg_w_buf(gspca_dev, index, seq, 8);
				seq += 8;
				index += 8;
				len -= 8;
			}
		}
	}
	/* not reached */
}
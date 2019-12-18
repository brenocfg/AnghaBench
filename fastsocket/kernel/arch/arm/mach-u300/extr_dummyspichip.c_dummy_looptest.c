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
typedef  int u8 ;
struct spi_device {TYPE_1__* master; struct pl022_config_chip* controller_data; int /*<<< orphan*/  dev; } ;
struct pl022_config_chip {int /*<<< orphan*/  data_size; } ;
struct dummy {int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* setup ) (struct spi_device*) ;} ;

/* Variables and functions */
 int DMA_TEST_SIZE ; 
 int EIO ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SSP_DATA_BITS_16 ; 
 int /*<<< orphan*/  SSP_DATA_BITS_8 ; 
 struct dummy* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 int spi_read (struct spi_device*,int*,int) ; 
 int spi_w8r8 (struct spi_device*,int) ; 
 int spi_write (struct spi_device*,int*,int) ; 
 int spi_write_then_read (struct spi_device*,int*,int,int*,int) ; 
 int sprintf (char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct spi_device*) ; 
 int /*<<< orphan*/  stub2 (struct spi_device*) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static ssize_t dummy_looptest(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct spi_device *spi = to_spi_device(dev);
	struct dummy *p_dummy = dev_get_drvdata(&spi->dev);

	/*
	 * WARNING! Do not dereference the chip-specific data in any normal
	 * driver for a chip. It is usually STATIC and shall not be read
	 * or written to. Your chip driver should NOT depend on fields in this
	 * struct, this is just used here to alter the behaviour of the chip
	 * in order to perform tests.
	 */
	struct pl022_config_chip *chip_info = spi->controller_data;
	int status;
	u8 txbuf[14] = {0xDE, 0xAD, 0xBE, 0xEF, 0x2B, 0xAD,
			0xCA, 0xFE, 0xBA, 0xBE, 0xB1, 0x05,
			0xF0, 0x0D};
	u8 rxbuf[14];
	u8 *bigtxbuf_virtual;
	u8 *bigrxbuf_virtual;

	if (mutex_lock_interruptible(&p_dummy->lock))
		return -ERESTARTSYS;

	bigtxbuf_virtual = kmalloc(DMA_TEST_SIZE, GFP_KERNEL);
	if (bigtxbuf_virtual == NULL) {
		status = -ENOMEM;
		goto out;
	}
	bigrxbuf_virtual = kmalloc(DMA_TEST_SIZE, GFP_KERNEL);

	/* Fill TXBUF with some happy pattern */
	memset(bigtxbuf_virtual, 0xAA, DMA_TEST_SIZE);

	/*
	 * Force chip to 8 bit mode
	 * WARNING: NEVER DO THIS IN REAL DRIVER CODE, THIS SHOULD BE STATIC!
	 */
	chip_info->data_size = SSP_DATA_BITS_8;
	/* You should NOT DO THIS EITHER */
	spi->master->setup(spi);

	/* Now run the tests for 8bit mode */
	pr_info("Simple test 1: write 0xAA byte, read back garbage byte "
		"in 8bit mode\n");
	status = spi_w8r8(spi, 0xAA);
	if (status < 0)
		pr_warning("Siple test 1: FAILURE: spi_write_then_read "
			   "failed with status %d\n", status);
	else
		pr_info("Simple test 1: SUCCESS!\n");

	pr_info("Simple test 2: write 8 bytes, read back 8 bytes garbage "
		"in 8bit mode (full FIFO)\n");
	status = spi_write_then_read(spi, &txbuf[0], 8, &rxbuf[0], 8);
	if (status < 0)
		pr_warning("Simple test 2: FAILURE: spi_write_then_read() "
			   "failed with status %d\n", status);
	else
		pr_info("Simple test 2: SUCCESS!\n");

	pr_info("Simple test 3: write 14 bytes, read back 14 bytes garbage "
		"in 8bit mode (see if we overflow FIFO)\n");
	status = spi_write_then_read(spi, &txbuf[0], 14, &rxbuf[0], 14);
	if (status < 0)
		pr_warning("Simple test 3: FAILURE: failed with status %d "
			   "(probably FIFO overrun)\n", status);
	else
		pr_info("Simple test 3: SUCCESS!\n");

	pr_info("Simple test 4: write 8 bytes with spi_write(), read 8 "
		"bytes garbage with spi_read() in 8bit mode\n");
	status = spi_write(spi, &txbuf[0], 8);
	if (status < 0)
		pr_warning("Simple test 4 step 1: FAILURE: spi_write() "
			   "failed with status %d\n", status);
	else
		pr_info("Simple test 4 step 1: SUCCESS!\n");
	status = spi_read(spi, &rxbuf[0], 8);
	if (status < 0)
		pr_warning("Simple test 4 step 2: FAILURE: spi_read() "
			   "failed with status %d\n", status);
	else
		pr_info("Simple test 4 step 2: SUCCESS!\n");

	pr_info("Simple test 5: write 14 bytes with spi_write(), read "
		"14 bytes garbage with spi_read() in 8bit mode\n");
	status = spi_write(spi, &txbuf[0], 14);
	if (status < 0)
		pr_warning("Simple test 5 step 1: FAILURE: spi_write() "
			   "failed with status %d (probably FIFO overrun)\n",
			   status);
	else
		pr_info("Simple test 5 step 1: SUCCESS!\n");
	status = spi_read(spi, &rxbuf[0], 14);
	if (status < 0)
		pr_warning("Simple test 5 step 2: FAILURE: spi_read() "
			   "failed with status %d (probably FIFO overrun)\n",
			   status);
	else
		pr_info("Simple test 5: SUCCESS!\n");

	pr_info("Simple test 6: write %d bytes with spi_write(), "
		"read %d bytes garbage with spi_read() in 8bit mode\n",
		DMA_TEST_SIZE, DMA_TEST_SIZE);
	status = spi_write(spi, &bigtxbuf_virtual[0], DMA_TEST_SIZE);
	if (status < 0)
		pr_warning("Simple test 6 step 1: FAILURE: spi_write() "
			   "failed with status %d (probably FIFO overrun)\n",
			   status);
	else
		pr_info("Simple test 6 step 1: SUCCESS!\n");
	status = spi_read(spi, &bigrxbuf_virtual[0], DMA_TEST_SIZE);
	if (status < 0)
		pr_warning("Simple test 6 step 2: FAILURE: spi_read() "
			   "failed with status %d (probably FIFO overrun)\n",
			   status);
	else
		pr_info("Simple test 6: SUCCESS!\n");


	/*
	 * Force chip to 16 bit mode
	 * WARNING: NEVER DO THIS IN REAL DRIVER CODE, THIS SHOULD BE STATIC!
	 */
	chip_info->data_size = SSP_DATA_BITS_16;
	/* You should NOT DO THIS EITHER */
	spi->master->setup(spi);

	pr_info("Simple test 7: write 0xAA byte, read back garbage byte "
		"in 16bit bus mode\n");
	status = spi_w8r8(spi, 0xAA);
	if (status == -EIO)
		pr_info("Simple test 7: SUCCESS! (expected failure with "
			"status EIO)\n");
	else if (status < 0)
		pr_warning("Siple test 7: FAILURE: spi_write_then_read "
			   "failed with status %d\n", status);
	else
		pr_warning("Siple test 7: FAILURE: spi_write_then_read "
			   "succeeded but it was expected to fail!\n");

	pr_info("Simple test 8: write 8 bytes, read back 8 bytes garbage "
		"in 16bit mode (full FIFO)\n");
	status = spi_write_then_read(spi, &txbuf[0], 8, &rxbuf[0], 8);
	if (status < 0)
		pr_warning("Simple test 8: FAILURE: spi_write_then_read() "
			   "failed with status %d\n", status);
	else
		pr_info("Simple test 8: SUCCESS!\n");

	pr_info("Simple test 9: write 14 bytes, read back 14 bytes garbage "
		"in 16bit mode (see if we overflow FIFO)\n");
	status = spi_write_then_read(spi, &txbuf[0], 14, &rxbuf[0], 14);
	if (status < 0)
		pr_warning("Simple test 9: FAILURE: failed with status %d "
			   "(probably FIFO overrun)\n", status);
	else
		pr_info("Simple test 9: SUCCESS!\n");

	pr_info("Simple test 10: write %d bytes with spi_write(), "
	       "read %d bytes garbage with spi_read() in 16bit mode\n",
	       DMA_TEST_SIZE, DMA_TEST_SIZE);
	status = spi_write(spi, &bigtxbuf_virtual[0], DMA_TEST_SIZE);
	if (status < 0)
		pr_warning("Simple test 10 step 1: FAILURE: spi_write() "
			   "failed with status %d (probably FIFO overrun)\n",
			   status);
	else
		pr_info("Simple test 10 step 1: SUCCESS!\n");

	status = spi_read(spi, &bigrxbuf_virtual[0], DMA_TEST_SIZE);
	if (status < 0)
		pr_warning("Simple test 10 step 2: FAILURE: spi_read() "
			   "failed with status %d (probably FIFO overrun)\n",
			   status);
	else
		pr_info("Simple test 10: SUCCESS!\n");

	status = sprintf(buf, "loop test complete\n");
	kfree(bigrxbuf_virtual);
	kfree(bigtxbuf_virtual);
 out:
	mutex_unlock(&p_dummy->lock);
	return status;
}
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
struct device {int dummy; } ;
struct sdio_func {struct device dev; } ;
struct i2400ms {struct sdio_func* func; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2400MS_BLK_SIZE ; 
 int /*<<< orphan*/  d_printf (int /*<<< orphan*/ ,struct device*,char*,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int sdio_memcpy_toio (struct sdio_func*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 

__attribute__((used)) static
int __i2400ms_send_barker(struct i2400ms *i2400ms,
			  const __le32 *barker, size_t barker_size)
{
	int  ret;
	struct sdio_func *func = i2400ms->func;
	struct device *dev = &func->dev;
	void *buffer;

	ret = -ENOMEM;
	buffer = kmalloc(I2400MS_BLK_SIZE, GFP_KERNEL);
	if (buffer == NULL)
		goto error_kzalloc;

	memcpy(buffer, barker, barker_size);
	sdio_claim_host(func);
	ret = sdio_memcpy_toio(func, 0, buffer, I2400MS_BLK_SIZE);
	sdio_release_host(func);

	if (ret < 0)
		d_printf(0, dev, "E: barker error: %d\n", ret);

	kfree(buffer);
error_kzalloc:
	return ret;
}
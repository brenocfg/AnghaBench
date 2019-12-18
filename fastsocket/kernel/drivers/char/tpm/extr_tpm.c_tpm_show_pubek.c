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
typedef  int u8 ;
struct TYPE_4__ {int* readpubek_out_buffer; } ;
struct TYPE_3__ {int /*<<< orphan*/  in; } ;
struct tpm_cmd_t {TYPE_2__ params; TYPE_1__ header; } ;
struct tpm_chip {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  READ_PUBEK_RESULT_SIZE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct tpm_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  tpm_readpubek_header ; 
 int transmit_cmd (struct tpm_chip*,struct tpm_cmd_t*,int /*<<< orphan*/ ,char*) ; 

ssize_t tpm_show_pubek(struct device *dev, struct device_attribute *attr,
		       char *buf)
{
	u8 *data;
	struct tpm_cmd_t tpm_cmd;
	ssize_t err;
	int i, rc;
	char *str = buf;

	struct tpm_chip *chip = dev_get_drvdata(dev);

	tpm_cmd.header.in = tpm_readpubek_header;
	err = transmit_cmd(chip, &tpm_cmd, READ_PUBEK_RESULT_SIZE,
			"attempting to read the PUBEK");
	if (err)
		goto out;

	/* 
	   ignore header 10 bytes
	   algorithm 32 bits (1 == RSA )
	   encscheme 16 bits
	   sigscheme 16 bits
	   parameters (RSA 12->bytes: keybit, #primes, expbit)  
	   keylenbytes 32 bits
	   256 byte modulus
	   ignore checksum 20 bytes
	 */
	data = tpm_cmd.params.readpubek_out_buffer;
	str +=
	    sprintf(str,
		    "Algorithm: %02X %02X %02X %02X\nEncscheme: %02X %02X\n"
		    "Sigscheme: %02X %02X\nParameters: %02X %02X %02X %02X"
		    " %02X %02X %02X %02X %02X %02X %02X %02X\n"
		    "Modulus length: %d\nModulus: \n",
		    data[10], data[11], data[12], data[13], data[14],
		    data[15], data[16], data[17], data[22], data[23],
		    data[24], data[25], data[26], data[27], data[28],
		    data[29], data[30], data[31], data[32], data[33],
		    be32_to_cpu(*((__be32 *) (data + 34))));

	for (i = 0; i < 256; i++) {
		str += sprintf(str, "%02X ", data[i + 38]);
		if ((i + 1) % 16 == 0)
			str += sprintf(str, "\n");
	}
out:
	rc = str - buf;
	return rc;
}
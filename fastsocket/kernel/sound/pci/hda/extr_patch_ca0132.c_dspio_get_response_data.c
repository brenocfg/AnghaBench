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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {unsigned int wait_scp_header; unsigned int scp_resp_header; unsigned int scp_resp_count; unsigned int wait_num_data; int /*<<< orphan*/  scp_resp_data; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ dspio_read (struct hda_codec*,unsigned int*) ; 
 int /*<<< orphan*/  dspio_read_multiple (struct hda_codec*,int /*<<< orphan*/ ,unsigned int*,unsigned int) ; 

__attribute__((used)) static int dspio_get_response_data(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int data = 0;
	unsigned int count;

	if (dspio_read(codec, &data) < 0)
		return -EIO;

	if ((data & 0x00ffffff) == spec->wait_scp_header) {
		spec->scp_resp_header = data;
		spec->scp_resp_count = data >> 27;
		count = spec->wait_num_data;
		dspio_read_multiple(codec, spec->scp_resp_data,
				    &spec->scp_resp_count, count);
		return 0;
	}

	return -EIO;
}
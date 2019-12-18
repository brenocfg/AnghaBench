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
struct mousedev_client {int* ps2; int bufsiz; int mode; int buffer; int /*<<< orphan*/  imexseq; int /*<<< orphan*/  impsseq; } ;

/* Variables and functions */
#define  MOUSEDEV_EMUL_EXPS 130 
#define  MOUSEDEV_EMUL_IMPS 129 
#define  MOUSEDEV_EMUL_PS2 128 
 int /*<<< orphan*/  mousedev_packet (struct mousedev_client*,int*) ; 

__attribute__((used)) static void mousedev_generate_response(struct mousedev_client *client,
					int command)
{
	client->ps2[0] = 0xfa; /* ACK */

	switch (command) {

	case 0xeb: /* Poll */
		mousedev_packet(client, &client->ps2[1]);
		client->bufsiz++; /* account for leading ACK */
		break;

	case 0xf2: /* Get ID */
		switch (client->mode) {
		case MOUSEDEV_EMUL_PS2:
			client->ps2[1] = 0;
			break;
		case MOUSEDEV_EMUL_IMPS:
			client->ps2[1] = 3;
			break;
		case MOUSEDEV_EMUL_EXPS:
			client->ps2[1] = 4;
			break;
		}
		client->bufsiz = 2;
		break;

	case 0xe9: /* Get info */
		client->ps2[1] = 0x60; client->ps2[2] = 3; client->ps2[3] = 200;
		client->bufsiz = 4;
		break;

	case 0xff: /* Reset */
		client->impsseq = client->imexseq = 0;
		client->mode = MOUSEDEV_EMUL_PS2;
		client->ps2[1] = 0xaa; client->ps2[2] = 0x00;
		client->bufsiz = 3;
		break;

	default:
		client->bufsiz = 1;
		break;
	}
	client->buffer = client->bufsiz;
}
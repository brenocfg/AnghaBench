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
struct zdap_ioctl {int addr; int value; unsigned char* data; int /*<<< orphan*/  cmd; } ;
struct ifreq {char* ifr_data; int /*<<< orphan*/  ifr_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IPPROTO_RAW ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  ZM_IOCTL_DMA_TEST ; 
 int /*<<< orphan*/  ZM_IOCTL_DURATION_MODE ; 
 int /*<<< orphan*/  ZM_IOCTL_ENCRYPTION_MODE ; 
 int /*<<< orphan*/  ZM_IOCTL_FRAG ; 
 int /*<<< orphan*/  ZM_IOCTL_GET_DEAGG_CNT ; 
 int /*<<< orphan*/  ZM_IOCTL_GET_TXCNT ; 
 int /*<<< orphan*/  ZM_IOCTL_KEY ; 
 int /*<<< orphan*/  ZM_IOCTL_MEM_DUMP ; 
 int /*<<< orphan*/  ZM_IOCTL_MEM_READ ; 
 int /*<<< orphan*/  ZM_IOCTL_MEM_WRITE ; 
 int /*<<< orphan*/  ZM_IOCTL_MIX_MODE ; 
 int /*<<< orphan*/  ZM_IOCTL_RATE ; 
 int /*<<< orphan*/  ZM_IOCTL_REG_DUMP ; 
 int /*<<< orphan*/  ZM_IOCTL_REG_READ ; 
 int /*<<< orphan*/  ZM_IOCTL_REG_TEST ; 
 int /*<<< orphan*/  ZM_IOCTL_REG_WRITE ; 
 int /*<<< orphan*/  ZM_IOCTL_RTS ; 
 int /*<<< orphan*/  ZM_IOCTL_RXD_DUMP ; 
 int /*<<< orphan*/  ZM_IOCTL_SCAN ; 
 int /*<<< orphan*/  ZM_IOCTL_SET_AES_KEY ; 
 int /*<<< orphan*/  ZM_IOCTL_SET_AES_MODE ; 
 int /*<<< orphan*/  ZM_IOCTL_SET_PIBSS_MODE ; 
 int /*<<< orphan*/  ZM_IOCTL_TALLY ; 
 int /*<<< orphan*/  ZM_IOCTL_TEST ; 
 int /*<<< orphan*/  ZM_IOCTL_TXD_DUMP ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* prgname ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  set_ioctl (int,struct ifreq*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscanf (char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

int main(int argc, char **argv)
{
    int sock;
    int addr, value;
    struct ifreq req;
    char *action = NULL;
    struct zdap_ioctl zdreq;

    prgname = argv[0];

    if (argc < 3) {
        fprintf(stderr,"%s: usage is \"%s <ifname> <operation> [<address>] [<value>]\"\n",
                prgname, prgname);
        fprintf(stderr,"valid operation: read, write, mem, reg,\n");
        fprintf(stderr,"               : txd, rxd, rmem, wmem\n");
        fprintf(stderr,"               : dmat, regt, test\n");

        fprintf(stderr,"    scan, Channel Scan\n");
        fprintf(stderr,"    rts <decimal>, Set RTS Threshold\n");
        fprintf(stderr,"    frag <decimal>, Set Fragment Threshold\n");
        fprintf(stderr,"    rate <0-28>, 0:AUTO, 1-4:CCK, 5-12:OFDM, 13-28:HT\n");
        fprintf(stderr,"    TBD mix <0 or 1>, Set 1 to enable mixed mode\n");
        fprintf(stderr,"    enc, <0-3>, 0=>OPEN, 1=>WEP64, 2=>WEP128, 3=>WEP256\n");
        fprintf(stderr,"    skey <key>, Set WEP key\n");
        fprintf(stderr,"    txcnt, Get TxQ Cnt\n");
        fprintf(stderr,"    dagcnt, Get Deaggregate Cnt\n");
        fprintf(stderr,"    durmode <mode>, Set Duration Mode 0=>HW, 1=>SW\n");
        fprintf(stderr,"    aeskey <user> <key>\n");
        fprintf(stderr,"    aesmode <mode>\n");
        fprintf(stderr,"    wlanmode <0,1> 0:Station mode, 1:PIBSS mode\n");
        fprintf(stderr,"    tal <0,1>, Get Current Tally Info, 0=>read, 1=>read and reset\n");

        exit(1);
    }

    strcpy(req.ifr_name, argv[1]);
    zdreq.addr = 0;
    zdreq.value = 0;

    /* a silly raw socket just for ioctl()ling it */
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sock < 0) {
        fprintf(stderr, "%s: socket(): %s\n", argv[0], strerror(errno));
        exit(1);
    }

    if (argc >= 4)
    {
        sscanf(argv[3], "%x", &addr);
    }

    if (argc >= 5)
    {
        sscanf(argv[4], "%x", &value);
    }

    zdreq.addr = addr;
    zdreq.value = value;

    if (!strcmp(argv[2], "read"))
    {
        zdreq.cmd = ZM_IOCTL_REG_READ;
    }
    else if (!strcmp(argv[2], "mem"))
    {
        zdreq.cmd = ZM_IOCTL_MEM_DUMP;
    }
    else if (!strcmp(argv[2], "write"))
    {
        zdreq.cmd = ZM_IOCTL_REG_WRITE;
    }
    else if (!strcmp(argv[2], "reg"))
    {
        zdreq.cmd = ZM_IOCTL_REG_DUMP;
    }
    else if (!strcmp(argv[2], "txd"))
    {
        zdreq.cmd = ZM_IOCTL_TXD_DUMP;
    }
    else if (!strcmp(argv[2], "rxd"))
    {
        zdreq.cmd = ZM_IOCTL_RXD_DUMP;
    }
    else if (!strcmp(argv[2], "rmem"))
    {
        zdreq.cmd = ZM_IOCTL_MEM_READ;
    }
    else if (!strcmp(argv[2], "wmem"))
    {
        zdreq.cmd = ZM_IOCTL_MEM_WRITE;
    }
    else if (!strcmp(argv[2], "dmat"))
    {
        zdreq.cmd = ZM_IOCTL_DMA_TEST;
    }
    else if (!strcmp(argv[2], "regt"))
    {
        zdreq.cmd = ZM_IOCTL_REG_TEST;
    }
    else if (!strcmp(argv[2], "test"))
    {
        zdreq.cmd = ZM_IOCTL_TEST;
    }
    else if (!strcmp(argv[2], "tal"))
    {
        sscanf(argv[3], "%d", &addr);
        zdreq.addr = addr;
        zdreq.cmd = ZM_IOCTL_TALLY;
    }
    else if (!strcmp(argv[2], "rts"))
    {
        sscanf(argv[3], "%d", &addr);
        zdreq.addr = addr;
        zdreq.cmd = ZM_IOCTL_RTS;
    }
    else if (!strcmp(argv[2], "mix"))
    {
        zdreq.cmd = ZM_IOCTL_MIX_MODE;
    }
    else if (!strcmp(argv[2], "frag"))
    {
        sscanf(argv[3], "%d", &addr);
        zdreq.addr = addr;
        zdreq.cmd = ZM_IOCTL_FRAG;
    }
    else if (!strcmp(argv[2], "scan"))
    {
        zdreq.cmd = ZM_IOCTL_SCAN;
    }
    else if (!strcmp(argv[2], "skey"))
    {
        zdreq.cmd = ZM_IOCTL_KEY;

        if (argc >= 4)
        {
            unsigned char temp[29];
            int i;
            int keyLen;
            int encType;

            keyLen = strlen(argv[3]);

            if (keyLen == 10)
            {
                sscanf(argv[3], "%02x%02x%02x%02x%02x", &temp[0], &temp[1],
                        &temp[2], &temp[3], &temp[4]);
            }
            else if (keyLen == 26)
            {
                sscanf(argv[3], "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
                        &temp[0], &temp[1], &temp[2], &temp[3], &temp[4],
                        &temp[5], &temp[6], &temp[7], &temp[8], &temp[9],
                         &temp[10], &temp[11], &temp[12]);
            }
            else if (keyLen == 58)
            {
                sscanf(argv[3], "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
                        &temp[0], &temp[1], &temp[2], &temp[3], &temp[4],
                        &temp[5], &temp[6], &temp[7], &temp[8], &temp[9],
                        &temp[10], &temp[11], &temp[12], &temp[13], &temp[14],
                        &temp[15], &temp[16], &temp[17], &temp[18], &temp[19],
                        &temp[20], &temp[21], &temp[22], &temp[23], &temp[24],
                        &temp[25], &temp[26], &temp[27], &temp[28]);
            }
            else
            {
                fprintf(stderr, "Invalid key length\n");
                exit(1);
            }
            zdreq.addr = keyLen/2;

            for(i=0; i<zdreq.addr; i++)
            {
                zdreq.data[i] = temp[i];
            }
        }
        else
        {
            printf("Error : Key required!\n");
        }
    }
    else if (!strcmp(argv[2], "rate"))
    {
        sscanf(argv[3], "%d", &addr);

        if (addr > 28)
        {
            fprintf(stderr, "Invalid rate, range:0~28\n");
            exit(1);
        }
        zdreq.addr = addr;
        zdreq.cmd = ZM_IOCTL_RATE;
    }
    else if (!strcmp(argv[2], "enc"))
    {
        sscanf(argv[3], "%d", &addr);

        if (addr > 3)
        {
            fprintf(stderr, "Invalid encryption mode, range:0~3\n");
            exit(1);
        }

        if (addr == 2)
        {
            addr = 5;
        }
        else if (addr == 3)
        {
            addr = 6;
        }

        zdreq.addr = addr;
        zdreq.cmd = ZM_IOCTL_ENCRYPTION_MODE;
    }
    else if (!strcmp(argv[2], "txcnt"))
    {
        zdreq.cmd = ZM_IOCTL_GET_TXCNT;
    }
    else if (!strcmp(argv[2], "dagcnt"))
    {
        sscanf(argv[3], "%d", &addr);

        if (addr != 0 && addr != 1)
        {
            fprintf(stderr, "The value should be 0 or 1\n");
            exit(0);
        }

        zdreq.addr = addr;
        zdreq.cmd = ZM_IOCTL_GET_DEAGG_CNT;
    }
    else if (!strcmp(argv[2], "durmode"))
    {
        sscanf(argv[3], "%d", &addr);

        if (addr != 0 && addr != 1)
        {
            fprintf(stderr, "The Duration mode should be 0 or 1\n");
            exit(0);
        }

        zdreq.addr = addr;
        zdreq.cmd = ZM_IOCTL_DURATION_MODE;
    }
    else if (!strcmp(argv[2], "aeskey"))
    {
        unsigned char temp[16];
        int i;

        sscanf(argv[3], "%d", &addr);

        sscanf(argv[4], "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", &temp[0], &temp[1], &temp[2], &temp[3], &temp[4], &temp[5], &temp[6], &temp[7], &temp[8], &temp[9], &temp[10], &temp[11], &temp[12], &temp[13], &temp[14], &temp[15]);

        for(i = 0; i < 16; i++)
        {
            zdreq.data[i] = temp[i];
        }

        zdreq.addr = addr;
        zdreq.cmd = ZM_IOCTL_SET_AES_KEY;
    }
    else if (!strcmp(argv[2], "aesmode"))
    {
        sscanf(argv[3], "%d", &addr);

        zdreq.addr = addr;
        zdreq.cmd = ZM_IOCTL_SET_AES_MODE;
    }
    else if (!strcmp(argv[2], "wlanmode"))
    {
        sscanf(argv[3], "%d", &addr);

        zdreq.addr = addr;
        zdreq.cmd = ZM_IOCTL_SET_PIBSS_MODE;
    }
    else
    {
	    fprintf(stderr, "error action\n");
        exit(1);
    }

    req.ifr_data = (char *)&zdreq;
    set_ioctl(sock, &req);

fail:
    exit(0);
}
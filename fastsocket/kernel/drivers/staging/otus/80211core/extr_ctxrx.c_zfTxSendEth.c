#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
typedef  int u16_t ;
struct zsMicVar {int dummy; } ;
struct zsFrag {int* seq; int* bufType; int* flag; int /*<<< orphan*/ ** buf; } ;
struct TYPE_7__ {int encryMode; int keyId; int cencKeyId; scalar_t__ wmeConnected; } ;
struct TYPE_6__ {int* bcHalKeyIdx; TYPE_1__* staTable; } ;
struct TYPE_8__ {scalar_t__ wlanMode; int fragThreshold; int /*<<< orphan*/ * seq; TYPE_3__ sta; TYPE_2__ ap; } ;
struct TYPE_5__ {int encryMode; int keyIdx; } ;

/* Variables and functions */
#define  ZM_AES 133 
#define  ZM_CENC 132 
 int ZM_INTERNAL_ALLOC_BUF ; 
 int /*<<< orphan*/  ZM_LV_2 ; 
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int ZM_SUCCESS ; 
#define  ZM_TKIP 131 
#define  ZM_WEP128 130 
#define  ZM_WEP256 129 
#define  ZM_WEP64 128 
 TYPE_4__* wd ; 
 size_t* zcUpToAc ; 
 int /*<<< orphan*/  zf80211FrameSend (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int*,int*,int,int,int*,int*,int,int,int,size_t,int) ; 
 int zfApFindSta (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zfApGetStaQosType (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  zfCopyToRxBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  zfTxBufferCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int zfTxGenWlanHeader (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int,int,int,int,int*,int*,int,int*,int*,int,int /*<<< orphan*/ *) ; 
 int zfTxGenWlanSnap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int zfTxGenWlanTail (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int*) ; 
 int /*<<< orphan*/  zfTxGetIpTosAndFrag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/ * zfwBufAllocate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfwBufSetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfwCopyBufContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_msg1_tx (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 int zmw_tx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

u16_t zfTxSendEth(zdev_t* dev, zbuf_t* buf, u16_t port, u16_t bufType, u16_t flag)
{
    u16_t err;
    //u16_t addrTblSize;
    //struct zsAddrTbl addrTbl;
    u16_t removeLen;
    u16_t header[(8+30+2+18)/2];    /* ctr+(4+a1+a2+a3+2+a4)+qos+iv */
    u16_t headerLen;
    u16_t mic[8/2];
    u16_t micLen;
    u16_t snap[8/2];
    u16_t snapLen;
    u16_t fragLen;
    u16_t frameLen;
    u16_t fragNum;
    struct zsFrag frag;
    u16_t i, j, id;
    u16_t offset;
    u16_t da[3];
    u16_t sa[3];
    u8_t up;
    u8_t qosType, keyIdx = 0;
    u16_t fragOff;
    u16_t newFlag;
    struct zsMicVar*  pMicKey;
    u8_t tkipFrameOffset = 0;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    newFlag = flag & 0xff00;
    flag = flag & 0xff;

    zm_msg1_tx(ZM_LV_2, "zfTxSendEth(), port=", port);

    /* Get IP TOS for QoS AC and IP frag offset */
    zfTxGetIpTosAndFrag(dev, buf, &up, &fragOff);

    //EOSP bit
    if (newFlag & 0x100)
    {
        up |= 0x10;
    }

#ifdef ZM_ENABLE_NATIVE_WIFI
    if ( wd->wlanMode == ZM_MODE_INFRASTRUCTURE )
    {
        /* DA */
        da[0] = zmw_tx_buf_readh(dev, buf, 16);
        da[1] = zmw_tx_buf_readh(dev, buf, 18);
        da[2] = zmw_tx_buf_readh(dev, buf, 20);
        /* SA */
        sa[0] = zmw_tx_buf_readh(dev, buf, 10);
        sa[1] = zmw_tx_buf_readh(dev, buf, 12);
        sa[2] = zmw_tx_buf_readh(dev, buf, 14);
    }
    else if ( wd->wlanMode == ZM_MODE_IBSS )
    {
        /* DA */
        da[0] = zmw_tx_buf_readh(dev, buf, 4);
        da[1] = zmw_tx_buf_readh(dev, buf, 6);
        da[2] = zmw_tx_buf_readh(dev, buf, 8);
        /* SA */
        sa[0] = zmw_tx_buf_readh(dev, buf, 10);
        sa[1] = zmw_tx_buf_readh(dev, buf, 12);
        sa[2] = zmw_tx_buf_readh(dev, buf, 14);
    }
    else if ( wd->wlanMode == ZM_MODE_AP )
    {
        /* DA */
        da[0] = zmw_tx_buf_readh(dev, buf, 4);
        da[1] = zmw_tx_buf_readh(dev, buf, 6);
        da[2] = zmw_tx_buf_readh(dev, buf, 8);
        /* SA */
        sa[0] = zmw_tx_buf_readh(dev, buf, 16);
        sa[1] = zmw_tx_buf_readh(dev, buf, 18);
        sa[2] = zmw_tx_buf_readh(dev, buf, 20);
    }
    else
    {
        //
    }
#else
    /* DA */
    da[0] = zmw_tx_buf_readh(dev, buf, 0);
    da[1] = zmw_tx_buf_readh(dev, buf, 2);
    da[2] = zmw_tx_buf_readh(dev, buf, 4);
    /* SA */
    sa[0] = zmw_tx_buf_readh(dev, buf, 6);
    sa[1] = zmw_tx_buf_readh(dev, buf, 8);
    sa[2] = zmw_tx_buf_readh(dev, buf, 10);
#endif
    //Decide Key Index in ATOM, No meaning in OTUS--CWYang(m)
    if (wd->wlanMode == ZM_MODE_AP)
    {
        keyIdx = wd->ap.bcHalKeyIdx[port];
        id = zfApFindSta(dev, da);
        if (id != 0xffff)
        {
            switch (wd->ap.staTable[id].encryMode)
            {
            case ZM_AES:
            case ZM_TKIP:
#ifdef ZM_ENABLE_CENC
            case ZM_CENC:
#endif //ZM_ENABLE_CENC
                keyIdx = wd->ap.staTable[id].keyIdx;
                break;
            }
        }
    }
    else
    {
        switch (wd->sta.encryMode)
        {
        case ZM_WEP64:
        case ZM_WEP128:
        case ZM_WEP256:
            keyIdx = wd->sta.keyId;
            break;
        case ZM_AES:
        case ZM_TKIP:
            if ((da[0] & 0x1))
                keyIdx = 5;
            else
                keyIdx = 4;
            break;
#ifdef ZM_ENABLE_CENC
        case ZM_CENC:
            keyIdx = wd->sta.cencKeyId;
            break;
#endif //ZM_ENABLE_CENC
        }
    }

    /* Create SNAP */
    removeLen = zfTxGenWlanSnap(dev, buf, snap, &snapLen);
    //zm_msg1_tx(ZM_LV_0, "fragOff=", fragOff);


/* ********************************************************************************************** */
/* Add 20071025 Mxzeng                                                                            */
/* ********************************************************************************************** */
/* ---------------------------------------------------------------------------------------------- */
/*  Ethernet : frameLen = zfwBufGetSize(dev, buf);                                                */
/* ---+--6--+--6--+--2--+-----20-----+-------------------------+------ Variable -------+--------- */
/*    |  DA |  SA | Type|  IP Header | TCP(20) UDP(12) ICMP(8) | Application Payload L |          */
/* ---+-----+-----+-----+------------+-------------------------+-----------------------+--------- */
/*  MSDU = 6 + 6 + 2 + ( Network Layer header ) + ( Transport Layer header ) + L                  */
/*                                                                                                */
/*  MSDU - DA - SA : frameLen -= removeLen;                                                       */
/* ---+--2--+-----20-----+-------------------------+------ Variable -------+--------------------- */
/*    | Type| IP Header  | TCP(20) UDP(12) ICMP(8) | Application Payload L |                      */
/* ---+-----+------------+-------------------------+-----------------------+--------------------- */
/*												  */
/*  MPDU : frameLen + mpduLengthOffset ;                                                          */
/* -+---2---+----2---+-6-+-6-+--6--+---2----+--1--+--1-+---1---+-------3------+-frameLen-+---4--+- */
/*  | frame |duration| DA|SA |BSSID|sequence|SNAP |SNAP|Control|    RFC 1042  |          |  FCS |  */
/*  |Control|        |   |   |     | number |DSAP |SSAP|       | encapsulation|          |      |  */
/* -+-------+--------+---+---+-----+--------+-----+----+-------+--------------+----------+------+- */
/* ----------------------------------------------------------------------------------------------- */

    if ( wd->sta.encryMode == ZM_TKIP )
        tkipFrameOffset = 8;

    fragLen = wd->fragThreshold + tkipFrameOffset;   // Fragmentation threshold for MPDU Lengths
    frameLen = zfwBufGetSize(dev, buf);    // MSDU Lengths
    frameLen -= removeLen;                 // MSDU Lengths - DA - SA

    /* #1st create MIC Length manually */
    micLen = 0;

    /* Access Category */
    if (wd->wlanMode == ZM_MODE_AP)
    {
        zfApGetStaQosType(dev, da, &qosType);
        if (qosType == 0)
        {
            up = 0;
        }
    }
    else if (wd->wlanMode == ZM_MODE_INFRASTRUCTURE)
    {
        if (wd->sta.wmeConnected == 0)
        {
            up = 0;
        }
    }
    else
    {
        /* TODO : STA QoS control field */
        up = 0;
    }

    /* #2nd Assign sequence number */
    zmw_enter_critical_section(dev);
    frag.seq[0] = ((wd->seq[zcUpToAc[up&0x7]]++) << 4);
    zmw_leave_critical_section(dev);

    /* #3rd Pass the total payload to generate MPDU length ! */
    frag.buf[0] = buf;
    frag.bufType[0] = bufType;
    frag.flag[0] = (u8_t)flag;
    fragNum = 1;

    headerLen = zfTxGenWlanHeader(dev, frag.buf[0], header, frag.seq[0],
                                  frag.flag[0], snapLen+micLen, removeLen, port, da, sa,
                                  up, &micLen, snap, snapLen, NULL);

    //zm_debug_msg1("#1 headerLen = ", headerLen);

    /* #4th Check the HeaderLen and determine whether the MPDU Lengths bigger than Fragmentation threshold  */
    /* If MPDU Lengths large than fragmentation threshold --> headerLen = 0 */
    if( headerLen != 0 )
    {
        zf80211FrameSend(dev, frag.buf[0], header, snapLen, da, sa, up,
                         headerLen, snap, mic, micLen, removeLen, frag.bufType[0],
                         zcUpToAc[up&0x7], keyIdx);
    }
    else //if( headerLen == 0 ) // Need to be fragmented
    {
        u16_t mpduLengthOffset;
        u16_t pseudSnapLen = 0;

        mpduLengthOffset = header[0] - frameLen; // For fragmentation threshold !

        micLen = zfTxGenWlanTail(dev, buf, snap, snapLen, mic); // Get snap and mic information

        fragLen = fragLen - mpduLengthOffset;

        //zm_debug_msg1("#2 frameLen = ", frameLen);
        //zm_debug_msg1("#3 fragThreshold = ", fragLen);

        /* fragmentation */
        if (frameLen >= fragLen)
        {
            //copy fragLen to frag
            i = 0;
            while( frameLen > 0 )
            {
                if ((frag.buf[i] = zfwBufAllocate(dev, fragLen+32)) != NULL)
                {
                    frag.bufType[i] = ZM_INTERNAL_ALLOC_BUF;
                    frag.seq[i] = frag.seq[0] + i;
                    offset = removeLen + i*fragLen;

                    /* Consider the offset if we consider snap length to the other fragmented frame */
                    if ( i >= 1 )
                        offset = offset + pseudSnapLen*(i-1);

                    if (frameLen > fragLen + pseudSnapLen)
                    {
                        frag.flag[i] = flag | 0x4; /* More data */
                        /* First fragment */
                        if (i == 0)
                        {
                            /* Add SNAP */
                            for (j=0; j<snapLen; j+=2)
                            {
                                zmw_tx_buf_writeh(dev, frag.buf[i], j, snap[(j>>1)]);
                            }
                            zfTxBufferCopy(dev, frag.buf[i], buf, snapLen, offset, fragLen);
                            zfwBufSetSize(dev, frag.buf[i], snapLen+fragLen);

                            /* Add pseud snap length to the other fragmented frame */
                            pseudSnapLen = snapLen;

                            frameLen -= fragLen;
                        }
                        /* Intermediate Fragment */
                        else
                        {
                            //zfTxBufferCopy(dev, frag.buf[i], buf, 0, offset, fragLen);
                            //zfwBufSetSize(dev, frag.buf[i], fragLen);

                            zfTxBufferCopy(dev, frag.buf[i], buf, 0, offset, fragLen+pseudSnapLen );
                            zfwBufSetSize(dev, frag.buf[i], fragLen+pseudSnapLen);

                            frameLen -= (fragLen+pseudSnapLen);
                        }
                        //frameLen -= fragLen;
                    }
                    else
                    {
                        /* Last fragment  */
                        zfTxBufferCopy(dev, frag.buf[i], buf, 0, offset, frameLen);
                        /* Add MIC if need */
                        if ( micLen )
                        {
                            zfCopyToRxBuffer(dev, frag.buf[i], (u8_t*) mic, frameLen, micLen);
                        }
                        zfwBufSetSize(dev, frag.buf[i], frameLen+micLen);
                        frameLen = 0;
                        frag.flag[i] = (u8_t)flag; /* No more data */
                    }
                    i++;
                }
                else
                {
                    break;
                }

                // Please pay attention to the index of the buf !!!
                // If write to null buf , the OS will crash !!!
                zfwCopyBufContext(dev, buf, frag.buf[i-1]);
            }
            fragNum = i;
            snapLen = micLen = removeLen = 0;

            zfwBufFree(dev, buf, 0);
        }

        for (i=0; i<fragNum; i++)
        {
            /* Create WLAN header(Control Setting + 802.11 header + IV) */
            headerLen = zfTxGenWlanHeader(dev, frag.buf[i], header, frag.seq[i],
                                    frag.flag[i], snapLen+micLen, removeLen, port, da, sa, up, &micLen,
                                    snap, snapLen, NULL);

            zf80211FrameSend(dev, frag.buf[i], header, snapLen, da, sa, up,
                             headerLen, snap, mic, micLen, removeLen, frag.bufType[i],
                             zcUpToAc[up&0x7], keyIdx);

        } /* for (i=0; i<fragNum; i++) */
    }

    return ZM_SUCCESS;
}
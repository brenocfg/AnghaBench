#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  scalar_t__ u8_t ;
typedef  size_t u16_t ;
struct zsFrag {int* seq; size_t* bufType; int /*<<< orphan*/ ** buf; scalar_t__* flag; } ;
struct aggControl {scalar_t__ ampduIndication; } ;
struct TYPE_15__ {size_t txDataByteCount; } ;
struct TYPE_14__ {int /*<<< orphan*/  txTraffic; } ;
struct TYPE_13__ {int /*<<< orphan*/  txMulticastOctets; int /*<<< orphan*/  txMulticastFrm; int /*<<< orphan*/  txBroadcastOctets; int /*<<< orphan*/  txBroadcastFrm; int /*<<< orphan*/  txUnicastOctets; int /*<<< orphan*/  txUnicastFrm; } ;
struct TYPE_12__ {int encryMode; scalar_t__ keyId; scalar_t__ cencKeyId; scalar_t__ wmeConnected; } ;
struct TYPE_11__ {scalar_t__* bcHalKeyIdx; TYPE_1__* staTable; } ;
struct TYPE_17__ {scalar_t__ wlanMode; size_t fragThreshold; TYPE_6__ trafTally; TYPE_5__ ledStruct; TYPE_4__ commTally; int /*<<< orphan*/ * seq; TYPE_3__ sta; TYPE_2__ ap; } ;
struct TYPE_16__ {int bar_ssn; } ;
struct TYPE_10__ {int encryMode; scalar_t__ keyIdx; } ;
typedef  TYPE_7__* TID_TX ;

/* Variables and functions */
#define  ZM_AES 133 
 scalar_t__ ZM_AGG_FIRST_MPDU ; 
#define  ZM_CENC 132 
 size_t ZM_EXTERNAL_ALLOC_BUF ; 
 size_t ZM_INTERNAL_ALLOC_BUF ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 int /*<<< orphan*/  ZM_LV_2 ; 
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 size_t ZM_SUCCESS ; 
#define  ZM_TKIP 131 
#define  ZM_WEP128 130 
#define  ZM_WEP256 129 
#define  ZM_WEP64 128 
 size_t addrTblSize ; 
 TYPE_9__* wd ; 
 size_t* zcUpToAc ; 
 size_t zfApFindSta (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  zfApGetStaQosType (int /*<<< orphan*/ *,size_t*,scalar_t__*) ; 
 size_t zfHpSend (int /*<<< orphan*/ *,size_t*,size_t,size_t*,size_t,size_t*,size_t,int /*<<< orphan*/ *,size_t,size_t,size_t,scalar_t__) ; 
 size_t zfTxGenWlanHeader (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int,scalar_t__,size_t,size_t,size_t,size_t*,size_t*,scalar_t__,size_t*,size_t*,size_t,struct aggControl*) ; 
 size_t zfTxGenWlanSnap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,size_t*) ; 
 size_t zfTxGenWlanTail (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,size_t,size_t*) ; 
 int /*<<< orphan*/  zfTxGetIpTosAndFrag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,size_t*) ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  zm_msg1_agg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zm_msg1_tx (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 size_t zmw_tx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t zfAggTxSendEth(zdev_t* dev, zbuf_t* buf, u16_t port, u16_t bufType, u8_t flag, struct aggControl *aggControl, TID_TX tid_tx)
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
    u16_t i, id;
    u16_t da[3];
    u16_t sa[3];
    u8_t up;
    u8_t qosType, keyIdx = 0;
    u16_t fragOff;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zm_msg1_tx(ZM_LV_2, "zfTxSendEth(), port=", port);

    /* Get IP TOS for QoS AC and IP frag offset */
    zfTxGetIpTosAndFrag(dev, buf, &up, &fragOff);

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
            if ((da[0]& 0x1))
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

    fragLen = wd->fragThreshold;
    frameLen = zfwBufGetSize(dev, buf);
    frameLen -= removeLen;

#if 0
    /* Create MIC */
    if ( (wd->wlanMode == ZM_MODE_INFRASTRUCTURE)&&
         (wd->sta.encryMode == ZM_TKIP) )
    {
        if ( frameLen > fragLen )
        {
            micLen = zfTxGenWlanTail(dev, buf, snap, snapLen, mic);
        }
        else
        {
            /* append MIC by HMAC */
            micLen = 8;
        }
    }
    else
    {
        micLen = 0;
    }
#else
    if ( frameLen > fragLen )
    {
        micLen = zfTxGenWlanTail(dev, buf, snap, snapLen, mic);
    }
    else
    {
        /* append MIC by HMAC */
        micLen = 0;
    }
#endif

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

    /* Assign sequence number */
    zmw_enter_critical_section(dev);
    frag.seq[0] = ((wd->seq[zcUpToAc[up&0x7]]++) << 4);
    if (aggControl && (ZM_AGG_FIRST_MPDU == aggControl->ampduIndication) ) {
        tid_tx->bar_ssn = frag.seq[0];

        zm_msg1_agg(ZM_LV_0, "start seq=", tid_tx->bar_ssn >> 4);
    }
    //tid_tx->baw_buf[tid_tx->baw_head-1].baw_seq=frag.seq[0];
    zmw_leave_critical_section(dev);


        frag.buf[0] = buf;
        frag.bufType[0] = bufType;
        frag.flag[0] = flag;
        fragNum = 1;

    for (i=0; i<fragNum; i++)
    {
        /* Create WLAN header(Control Setting + 802.11 header + IV) */
        if (up !=0 ) zm_debug_msg1("up not 0, up=",up);
        headerLen = zfTxGenWlanHeader(dev, frag.buf[i], header, frag.seq[i],
                                      frag.flag[i], snapLen+micLen, removeLen,
                                      port, da, sa, up, &micLen, snap, snapLen,
                                      aggControl);

        /* Get buffer DMA address */
        //if ((addrTblSize = zfwBufMapDma(dev, frag.buf[i], &addrTbl)) == 0)
        //if ((addrTblSize = zfwMapTxDma(dev, frag.buf[i], &addrTbl)) == 0)
        //{
        //    err = ZM_ERR_BUFFER_DMA_ADDR;
        //    goto zlError;
        //}

        /* Flush buffer on cache */
        //zfwBufFlush(dev, frag.buf[i]);

#if 0
        zm_msg1_tx(ZM_LV_0, "headerLen=", headerLen);
        zm_msg1_tx(ZM_LV_0, "snapLen=", snapLen);
        zm_msg1_tx(ZM_LV_0, "micLen=", micLen);
        zm_msg1_tx(ZM_LV_0, "removeLen=", removeLen);
        zm_msg1_tx(ZM_LV_0, "addrTblSize=", addrTblSize);
        zm_msg1_tx(ZM_LV_0, "frag.bufType[0]=", frag.bufType[0]);
#endif

        fragLen = zfwBufGetSize(dev, frag.buf[i]);
        if ((da[0]&0x1) == 0)
        {
            wd->commTally.txUnicastFrm++;
            wd->commTally.txUnicastOctets += (fragLen+snapLen);
        }
        else if ((da[0]& 0x1))
        {
            wd->commTally.txBroadcastFrm++;
            wd->commTally.txBroadcastOctets += (fragLen+snapLen);
        }
        else
        {
            wd->commTally.txMulticastFrm++;
            wd->commTally.txMulticastOctets += (fragLen+snapLen);
        }
        wd->ledStruct.txTraffic++;

#if 0 //Who care this?
        if ( (i)&&(i == (fragNum-1)) )
        {
            wd->trafTally.txDataByteCount -= micLen;
        }
#endif

        /*if (aggControl->tid_baw && aggControl->aggEnabled) {
            struct baw_header_r header_r;

            header_r.header      = header;
            header_r.mic         = mic;
            header_r.snap        = snap;
            header_r.headerLen   = headerLen;
            header_r.micLen      = micLen;
            header_r.snapLen     = snapLen;
            header_r.removeLen   = removeLen;
            header_r.keyIdx      = keyIdx;

            BAW->insert(dev, buf, tid_tx->bar_ssn >> 4, aggControl->tid_baw, 0, &header_r);
        }*/

        if ((err = zfHpSend(dev, header, headerLen, snap, snapLen,
                             mic, micLen, frag.buf[i], removeLen,
                             frag.bufType[i], zcUpToAc[up&0x7], keyIdx)) != ZM_SUCCESS)
        {
            goto zlError;
        }


        continue;

zlError:
        if (frag.bufType[i] == ZM_EXTERNAL_ALLOC_BUF)
        {
            zfwBufFree(dev, frag.buf[i], err);
        }
        else if (frag.bufType[i] == ZM_INTERNAL_ALLOC_BUF)
        {
            zfwBufFree(dev, frag.buf[i], 0);
        }
        else
        {
            zm_assert(0);
        }
    } /* for (i=0; i<fragNum; i++) */

    return ZM_SUCCESS;
}
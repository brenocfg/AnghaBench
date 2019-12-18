#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u32_t ;
typedef  int u16_t ;
struct zsWlanAssoFrameHeader {scalar_t__ status; int aid; } ;
struct TYPE_7__ {int ChannelInfo; } ;
struct TYPE_6__ {int HtCapInfo; } ;
struct TYPE_8__ {TYPE_2__ HtInfo; TYPE_1__ HtCap; } ;
struct TYPE_9__ {scalar_t__ connectState; int EnableHT; int wmeConnected; int wmeEnabled; scalar_t__ asocRspFrameBodySize; int* asocRspFrameBody; int htCtrlBandwidth; int SWEncryptEnable; int HT2040; int aid; int rxBeaconCount; scalar_t__ connection_11b; int /*<<< orphan*/  bssid; int /*<<< orphan*/  connectByReasso; scalar_t__ failCntOfReasso; scalar_t__ SG40; int /*<<< orphan*/  connPowerInHalfDbm; scalar_t__ oppositeCount; TYPE_3__ ie; int /*<<< orphan*/  wmeQosInfo; int /*<<< orphan*/  qosInfo; } ;
struct TYPE_10__ {scalar_t__ ExtOffset; int addbaCount; int CurrentTxRateKbps; int CurrentRxRateKbps; TYPE_4__ sta; int /*<<< orphan*/  (* zfcbConnectNotify ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ addbaComplete; } ;

/* Variables and functions */
 int ExtHtCap_RIFSMode ; 
 int /*<<< orphan*/  FALSE ; 
 int HTCAP_SupChannelWidthSet ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ZM_CACHED_FRAMEBODY_SIZE ; 
 int /*<<< orphan*/  ZM_EVENT_TIMEOUT_ADDBA ; 
 scalar_t__ ZM_HP_CAP_11N_ONE_TX_STREAM ; 
 int /*<<< orphan*/  ZM_STATUS_MEDIA_CONNECT ; 
 int /*<<< orphan*/  ZM_STATUS_MEDIA_DISCONNECT_ASOC_FAILED ; 
 scalar_t__ ZM_STA_CONN_STATE_ASSOCIATE ; 
 int /*<<< orphan*/  ZM_STA_STATE_CONNECTED ; 
 int ZM_STA_UAPSD_ENABLE_BIT ; 
 int ZM_STA_WME_ENABLE_BIT ; 
 int ZM_SW_TKIP_ENCRY_EN ; 
 int ZM_SW_WEP_ENCRY_EN ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* wd ; 
 int /*<<< orphan*/  zfAggSendAddbaRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfChangeAdapterState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfCopyFromRxBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int zfFindWifiElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ zfHpCapability (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpGetTransmitPower (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfPowerSavingMgrConnectNotify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaConnectFail (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfStaIsConnecting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaSetOppositeInfoFromRxBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaStoreAsocRspIe (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaUpdateWmeParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfTimerSchedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

void zfStaProcessAsocRsp(zdev_t* dev, zbuf_t* buf)
{
    struct zsWlanAssoFrameHeader* pAssoFrame;
    u8_t  pBuf[sizeof(struct zsWlanAssoFrameHeader)];
    u16_t offset;
    u32_t i;
    u32_t oneTxStreamCap;

    zmw_get_wlan_dev(dev);

    if ( !zfStaIsConnecting(dev) )
    {
        return;
    }

    pAssoFrame = (struct zsWlanAssoFrameHeader*) pBuf;
    zfCopyFromRxBuffer(dev, buf, pBuf, 0, sizeof(struct zsWlanAssoFrameHeader));

    if ( wd->sta.connectState == ZM_STA_CONN_STATE_ASSOCIATE )
    {
        if ( pAssoFrame->status == 0 )
        {
            zm_debug_msg0("ZM_STA_STATE_CONNECTED");

            if (wd->sta.EnableHT == 1)
            {
                wd->sta.wmeConnected = 1;
            }
            if ((wd->sta.wmeEnabled & ZM_STA_WME_ENABLE_BIT) != 0) //WME enabled
            {
                /* Asoc rsp may contain WME parameter element */
                if ((offset = zfFindWifiElement(dev, buf, 2, 1)) != 0xffff)
                {
                    zm_debug_msg0("WME enable");
                    wd->sta.wmeConnected = 1;
                    if ((wd->sta.wmeEnabled & ZM_STA_UAPSD_ENABLE_BIT) != 0)
                    {
                        if ((zmw_rx_buf_readb(dev, buf, offset+8) & 0x80) != 0)
                        {
                            zm_debug_msg0("UAPSD enable");
                            wd->sta.qosInfo = wd->sta.wmeQosInfo;
                        }
                    }

                    zfStaUpdateWmeParameter(dev, buf);
                }
            }


            //Store asoc response frame body, for VISTA only
            wd->sta.asocRspFrameBodySize = zfwBufGetSize(dev, buf)-24;
            if (wd->sta.asocRspFrameBodySize > ZM_CACHED_FRAMEBODY_SIZE)
            {
                wd->sta.asocRspFrameBodySize = ZM_CACHED_FRAMEBODY_SIZE;
            }
            for (i=0; i<wd->sta.asocRspFrameBodySize; i++)
            {
                wd->sta.asocRspFrameBody[i] = zmw_rx_buf_readb(dev, buf, i+24);
            }

            zfStaStoreAsocRspIe(dev, buf);
            if (wd->sta.EnableHT &&
                ((wd->sta.ie.HtCap.HtCapInfo & HTCAP_SupChannelWidthSet) != 0) &&
                (wd->ExtOffset != 0))
            {
                wd->sta.htCtrlBandwidth = 1;
            }
            else
            {
                wd->sta.htCtrlBandwidth = 0;
            }

            //Set channel according to AP's configuration
            //zfCoreSetFrequencyEx(dev, wd->frequency, wd->BandWidth40,
            //        wd->ExtOffset, NULL);

            if (wd->sta.EnableHT == 1)
            {
                wd->addbaComplete = 0;

                if ((wd->sta.SWEncryptEnable & ZM_SW_TKIP_ENCRY_EN) == 0 &&
                    (wd->sta.SWEncryptEnable & ZM_SW_WEP_ENCRY_EN) == 0)
                {
                    wd->addbaCount = 1;
                    zfAggSendAddbaRequest(dev, wd->sta.bssid, 0, 0);
                    zfTimerSchedule(dev, ZM_EVENT_TIMEOUT_ADDBA, 100);
                }
            }

            /* set RIFS support */
            if(wd->sta.ie.HtInfo.ChannelInfo & ExtHtCap_RIFSMode)
            {
                wd->sta.HT2040 = 1;
//                zfHpSetRifs(dev, wd->sta.EnableHT, 1, (wd->sta.currentFrequency < 3000)? 1:0);
            }

            wd->sta.aid = pAssoFrame->aid & 0x3fff;
            wd->sta.oppositeCount = 0;    /* reset opposite count */
            zfStaSetOppositeInfoFromRxBuf(dev, buf);

            wd->sta.rxBeaconCount = 16;

            zfChangeAdapterState(dev, ZM_STA_STATE_CONNECTED);
            wd->sta.connPowerInHalfDbm = zfHpGetTransmitPower(dev);
            if (wd->zfcbConnectNotify != NULL)
            {
                if (wd->sta.EnableHT != 0) /* 11n */
            	{
    		        oneTxStreamCap = (zfHpCapability(dev) & ZM_HP_CAP_11N_ONE_TX_STREAM);
    		        if (wd->sta.htCtrlBandwidth == 1) /* HT40*/
    		        {
    					if(oneTxStreamCap) /* one Tx stream */
    				    {
    				        if (wd->sta.SG40)
    				        {
    				            wd->CurrentTxRateKbps = 150000;
    						    wd->CurrentRxRateKbps = 300000;
    				        }
    				        else
    				        {
    				            wd->CurrentTxRateKbps = 135000;
    						    wd->CurrentRxRateKbps = 270000;
    				        }
    				    }
    				    else /* Two Tx streams */
    				    {
    				        if (wd->sta.SG40)
    				        {
    				            wd->CurrentTxRateKbps = 300000;
    						    wd->CurrentRxRateKbps = 300000;
    				        }
    				        else
    				        {
    				            wd->CurrentTxRateKbps = 270000;
    						    wd->CurrentRxRateKbps = 270000;
    				        }
    				    }
    		        }
    		        else /* HT20 */
    		        {
    		            if(oneTxStreamCap) /* one Tx stream */
    				    {
    				        wd->CurrentTxRateKbps = 650000;
    						wd->CurrentRxRateKbps = 130000;
    				    }
    				    else /* Two Tx streams */
    				    {
    				        wd->CurrentTxRateKbps = 130000;
    					    wd->CurrentRxRateKbps = 130000;
    				    }
    		        }
                }
                else /* 11abg */
                {
                    if (wd->sta.connection_11b != 0)
                    {
                        wd->CurrentTxRateKbps = 11000;
    			        wd->CurrentRxRateKbps = 11000;
                    }
                    else
                    {
                        wd->CurrentTxRateKbps = 54000;
    			        wd->CurrentRxRateKbps = 54000;
    			    }
                }


                wd->zfcbConnectNotify(dev, ZM_STATUS_MEDIA_CONNECT, wd->sta.bssid);
            }
            wd->sta.connectByReasso = TRUE;
            wd->sta.failCntOfReasso = 0;

            zfPowerSavingMgrConnectNotify(dev);

            /* Disable here because fixed rate is only for test, TBD. */
            //if (wd->sta.EnableHT)
            //{
            //    wd->txMCS = 7; //Rate = 65Mbps
            //    wd->txMT = 2; // Ht rate
            //    wd->enableAggregation = 2; // Enable Aggregation
            //}
        }
        else
        {
            zm_debug_msg1("association failed, status = ",
                          pAssoFrame->status);

            zm_debug_msg0("ZM_STA_STATE_DISCONNECT");
            wd->sta.connectByReasso = FALSE;
            zfStaConnectFail(dev, ZM_STATUS_MEDIA_DISCONNECT_ASOC_FAILED, wd->sta.bssid, 3);
        }
    }

}
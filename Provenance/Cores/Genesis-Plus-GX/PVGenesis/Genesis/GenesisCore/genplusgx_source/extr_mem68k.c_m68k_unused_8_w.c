void m68k_unused_8_w(unsigned int address, unsigned int data)
{
#ifdef LOGERROR
  error("Unused write8 %08X = %02X (%08X)\n", address, data, m68k_get_reg(M68K_REG_PC));
#endif
}